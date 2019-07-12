#include "output.h"

int output_open(output_t *out, char *dev_label)
{
    out->device = device_get_binding(dev_label);
    out->dev_label = dev_label;
    out->state = 1;
    return 0;
}

int output_configure(output_t *out, u32_t pin, int flags)
{
    out->pin = pin;
    gpio_pin_configure(out->device, pin, flags);
    gpio_pin_write(out->device, pin, out->state);
    return 0;
}

int output_set(output_t *out, u8_t value)
{
    out->state = value;
    gpio_pin_write(out->device, out->pin, out->state);
    return 0;
}

u8_t output_digital_invert(output_t *out)
{
    u8_t inverted = ~out->state & 1;
    return inverted;
}