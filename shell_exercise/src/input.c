#include "input.h"
#include <misc/printk.h>

static struct gpio_callback buttons_cb;

int input_open(input_t *in, char *dev_label)
{
    in->device = device_get_binding(dev_label);
    in->dev_label = dev_label;
    in->gpio_callback = buttons_cb;
    in->pin = NULL;
    return 0;
}

int input_configure(input_t *in, u32_t pin, int flags, gpio_callback_handler_t cb)
{
    in->pin = pin;
    gpio_pin_configure(in->device, pin, flags);
    gpio_init_callback(&in->gpio_callback, cb, BIT(pin));
    gpio_add_callback(in->device, &in->gpio_callback);
    gpio_pin_enable_callback(in->device, pin);
    return 0;
}

int input_read(input_t *in, u32_t *state)
{
    if(in->pin != NULL)
    {
        gpio_pin_read(in->device, in->pin, state);
    }
    else
    {
        
    }
    
    return 0;
}