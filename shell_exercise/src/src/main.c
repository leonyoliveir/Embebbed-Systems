#include <zephyr.h>
#include <shell/shell.h>
#include "defines.h"
#include "input.h"
#include "output.h"

input_t button1, button2, button3, button4;
output_t led1, led2, led3, led4;

static int test_swap(const struct shell *shell, size_t argc, char **argv)
{
    char led_index = *(*(argv+1));
    switch(led_index)
    {
        case '1':
            output_digital_invert(&led1);
            break;
        case '2':
            output_digital_invert(&led2);
            break;
        case '3':
            output_digital_invert(&led3);
            break;
        case '4':
            output_digital_invert(&led4);
            break;
        default:
            shell_print(shell, "Please, choose an existent led!");
            return -1;
    }
    return 0;
}

static int test_blink(const struct shell *shell, size_t argc, char **argv)
{
    output_set(&led1, 1);
    output_set(&led2, 1);
    output_set(&led3, 1);
    output_set(&led4, 1);
    k_sleep(SLEEP_TIME);

    output_set(&led1, 0);
    k_sleep(SLEEP_TIME);
    output_set(&led1, 1);
    k_sleep(SLEEP_TIME);

    output_set(&led2, 0);
    k_sleep(SLEEP_TIME);
    output_set(&led2, 1);
    k_sleep(SLEEP_TIME);

    output_set(&led3, 0);
    k_sleep(SLEEP_TIME);
    output_set(&led3, 1);
    k_sleep(SLEEP_TIME);

    output_set(&led4, 0);
    k_sleep(SLEEP_TIME);
    output_set(&led4, 1);
    k_sleep(SLEEP_TIME);

    output_set(&led1, 0);
    output_set(&led2, 0);
    output_set(&led3, 0);
    output_set(&led4, 0);
    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(tests,
    SHELL_CMD_ARG(invert, NULL, "Invert selected led value command", test_swap, 2, NULL),
    SHELL_CMD_ARG(blink, NULL, "Test leds operation command", test_blink, 1, NULL),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(test, &tests, "Testing leds commands", NULL);

void buttons_callback(struct device *sw, struct gpio_callback *cb, u32_t pins)
{
    if(pins & 1 << PIN_SW0)
    {
        printk("Received new interruption from button 1\n");
        output_digital_invert(&led1);   
    }
    if(pins & 1 << PIN_SW1)
    {
        printk("Received new interruption from button 2\n");
        output_digital_invert(&led2);
    }
    if(pins & 1 << PIN_SW2)
    {
        printk("Received new interruption from button 3\n");
        output_digital_invert(&led3);
    }
    if(pins & 1 << PIN_SW3)
    {
        printk("Received new interruption from button 4\n");
        output_digital_invert(&led4);
    }   
    printk("Interruption ended\n");
}

int main(void)
{
    input_new(&button1, PORT_SW0, PIN_SW0, buttons_callback);
    input_new(&button2, PORT_SW1, PIN_SW1, buttons_callback);
    input_new(&button3, PORT_SW2, PIN_SW2, buttons_callback);
    input_new(&button4, PORT_SW3, PIN_SW3, buttons_callback);

    output_new(&led1, PORT_LED0, PIN_LED0);
    output_new(&led2, PORT_LED1, PIN_LED1);
    output_new(&led3, PORT_LED2, PIN_LED2);
    output_new(&led4, PORT_LED3, PIN_LED3);

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