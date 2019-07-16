#include "output.h"
#include <misc/printk.h>

#define ERROR_CODE -1
#define OUTPUT_FLAGS    GPIO_DIR_OUT

int output_open(output_t *out, char *dev_label)
{
    out->device = device_get_binding(dev_label);
    out->dev_label = dev_label;
    out->state = 1;
    out->pin = (u32_t) NULL;
    if(output_check_error(out))
    {
        return ERROR_CODE;
    }
    printk("New output initialized succesfully in the device %s\n", dev_label);
    return 0;
}

int output_configure(output_t *out, u32_t pin, int flags)
{
    if(output_check_error(out))
    {
        return ERROR_CODE;
    }
    out->pin = pin;
    gpio_pin_configure(out->device, pin, flags);
    gpio_pin_write(out->device, pin, out->state);
    printk("Output configured succesfully at pin %d\n", pin);
    return 0; 
}

int output_set(output_t *out, u8_t value)
{
    if(output_check_error(out))
    {
        return ERROR_CODE;
    }
    else if(out->pin == (u32_t) NULL)
    {
        printk("ERROR! First configure device\n");
        return ERROR_CODE;
    }
    out->state = value;
    gpio_pin_write(out->device, out->pin, out->state);
    printk("Output at pin %d changed state to %d\n", out->pin, out->state);
    return 0;
}

int output_digital_invert(output_t *out)
{
    if(output_check_error(out))
    {
        return ERROR_CODE;
    }
    u8_t inverted = ~out->state & 1;
    output_set(out, inverted);
    return 0;
}

int output_check_error(output_t *out)
{
    if(!out->device)
    {
        printk("ERROR! First iniatilize device\n");
        return ERROR_CODE;
    }
    return 0;
}

int output_new(output_t *out, char* dev_label, u32_t pin)
{
    printk("Initializing new output...\n");
    output_open(out, dev_label);
    printk("Setting the new output...\n");
    output_configure(out, pin, OUTPUT_FLAGS);
    printk("Finished new output initializing succesfully!\n");
    return 0;
}