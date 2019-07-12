#include <zephyr.h>
#include "defines.h"
#include "input.h"
#include "output.h"

input_t button1, button2, button3, button4;
output_t led1, led2, led3, led4;

void buttons_callback(struct device *sw, struct gpio_callback *cb, u32_t pins)
{
    if(pins & 1 << PIN_SW0)
    {
        u8_t new_value = output_digital_invert(&led1);
        output_set(&led1, new_value);
    }
    if(pins & 1 << PIN_SW1)
    {
        u8_t new_value = output_digital_invert(&led2);
        output_set(&led2, new_value);
    }
    if(pins & 1 << PIN_SW2)
    {
        u8_t new_value = output_digital_invert(&led3);
        output_set(&led3, new_value);
    }
    if(pins & 1 << PIN_SW3)
    {
        u8_t new_value = output_digital_invert(&led4);
        output_set(&led4, new_value);
    }   
}

int main(void)
{
    input_open(&button1, PORT_SW0);
    input_configure(&button1, PIN_SW0, INPUT_FLAGS, buttons_callback);
    input_open(&button2, PORT_SW1);
    input_configure(&button2, PIN_SW1, INPUT_FLAGS, buttons_callback);
    input_open(&button3, PORT_SW2);
    input_configure(&button3, PIN_SW2, INPUT_FLAGS, buttons_callback);
    input_open(&button4, PORT_SW3);
    input_configure(&button4, PIN_SW3, INPUT_FLAGS, buttons_callback);

    output_open(&led1, PORT_LED0);
    output_configure(&led1, PIN_LED0, OUTPUT_FLAGS);
    output_open(&led2, PORT_LED1);
    output_configure(&led2, PIN_LED1, OUTPUT_FLAGS);
    output_open(&led3, PORT_LED2);
    output_configure(&led3, PIN_LED2, OUTPUT_FLAGS);
    output_open(&led4, PORT_LED3);
    output_configure(&led4, PIN_LED3, OUTPUT_FLAGS);

    while(1)
    {
        u32_t value = 0U;

        input_read(&button1, &value);
        input_read(&button2, &value);
        input_read(&button3, &value);
        input_read(&button4, &value);
		k_sleep(SLEEP_TIME);
    }
    return 0;
}