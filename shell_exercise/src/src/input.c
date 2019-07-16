#include "input.h"
#include <misc/printk.h>

#define ERROR_CODE -1
#define INTERRUPT       GPIO_INT
#define FALL_EDGE       (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#define DEBOUNCE        GPIO_INT_DEBOUNCE
#define PULL_UP         GPIO_PUD_PULL_UP
#define INPUT_FLAGS     (GPIO_DIR_IN | INTERRUPT | FALL_EDGE | DEBOUNCE | PULL_UP)

int input_open(input_t *in, char *dev_label)
{
    in->device = device_get_binding(dev_label);
    in->dev_label = dev_label;
    in->pin = (u32_t) NULL;
    if(input_check_error(in))
    {
        return ERROR_CODE;
    }
    printk("New input initialized succesfully in the device %s\n", dev_label);
    return 0;
}

int input_configure(input_t *in, u32_t pin, int flags, gpio_callback_handler_t cb)
{
    if(input_check_error(in))
    {
        return ERROR_CODE;
    }
    in->pin = pin;
    gpio_pin_configure(in->device, pin, flags);
    gpio_init_callback(&in->gpio_callback, cb, BIT(pin));
    gpio_add_callback(in->device, &in->gpio_callback);
    gpio_pin_enable_callback(in->device, pin);
    printk("Input configured succesfully at pin %d\n", pin);
    return 0;
}

int input_read(input_t *in, u32_t *state)
{
    if(input_check_error(in))
    {
        return ERROR_CODE;
    }
    else if(in->pin == (u32_t) NULL)
    {
        printk("ERROR! First, configure device\n");
        return ERROR_CODE;
    }
    gpio_pin_read(in->device, in->pin, state);
    return 0;
}

int input_check_error(input_t *in)
{
    if(!in->device)
    {
        printk("ERROR! First iniatilize device\n");
        return ERROR_CODE;
    }
    return 0;
}

int input_new(input_t *in, char* dev_label, u32_t pin, gpio_callback_handler_t cb)
{
    printk("Initializing new input...\n");
    input_open(in, dev_label);
    printk("Setting the new input...\n");
    input_configure(in, pin, INPUT_FLAGS, cb);
    printk("Finished new input initializing succesfully!\n");
    return 0;
}