#include <zephyr.h>
#include <device.h>
#include <gpio.h>

#define PORT_LED0   LED0_GPIO_CONTROLLER
#define PORT_LED1   LED1_GPIO_CONTROLLER
#define PORT_LED2   LED2_GPIO_CONTROLLER
#define PORT_LED3   LED3_GPIO_CONTROLLER
#define PIN_LED0    LED0_GPIO_PIN
#define PIN_LED1    LED1_GPIO_PIN
#define PIN_LED2    LED2_GPIO_PIN
#define PIN_LED3    LED3_GPIO_PIN

#define PORT_SW0	SW0_GPIO_CONTROLLER
#define PORT_SW1    SW1_GPIO_CONTROLLER
#define PORT_SW2    SW2_GPIO_CONTROLLER
#define PORT_SW3    SW3_GPIO_CONTROLLER
#define PIN_SW0     SW0_GPIO_PIN
#define PIN_SW1     SW1_GPIO_PIN
#define PIN_SW2     SW2_GPIO_PIN
#define PIN_SW3     SW3_GPIO_PIN

#define INTERRUPT   GPIO_INT
#define FALL_EDGE   (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#define DEBOUNCE    GPIO_INT_DEBOUNCE
#define PULL_UP     GPIO_PUD_PULL_UP
#define SW_FLAGS    (GPIO_DIR_IN | INTERRUPT | FALL_EDGE | DEBOUNCE | PULL_UP)
#define SLEEP_TIME 500

// STRUCT THAT WILL STORE THE ACTUAL VALUES OF THE LEDS ON BOARD
// EACH LED VALUE WILL BE STORED ON A BIT
struct led
{
    int led1: 1;
    int led2: 1;
    int led3: 1;
    int led4: 1;
};

// INSTANCING STRUCTS DEVICE FOR THE BUTTONS AND LEDS
struct device *button1;
struct device *button2;
struct device *button3;
struct device *button4;

struct device *led1;
struct device *led2;
struct device *led3;
struct device *led4;

// INSTANCING STRUCTS FOR THE CALLBACK OF BUTTONS INTERRUPTS
static struct gpio_callback sw_1;
static struct gpio_callback sw_2;
static struct gpio_callback sw_3;
static struct gpio_callback sw_4;

// INSTANCING THE STRUCT TO STORE THE VALUES OF LEDS, INITIALIZING THEM WITH VALUE 1
static struct led leds = {1, 1, 1, 1};

// THE CALLBACK FOR EACH BUTTON INTERRUPT WILL CALL THE FUNCTION THAT WILL CHANGE
// THE CORRESPONDENT LED VALUE, USING THE INVERSOR OPERATOR
void sw1_callback(struct device *sw, struct gpio_callback *cb, u32_t pins)
{
    leds.led1 = ~leds.led1;
    gpio_pin_write(led1, PIN_LED0, leds.led1);
}

void sw2_callback(struct device *sw, struct gpio_callback *cb, u32_t pins)
{
    leds.led2 = ~leds.led2;
    gpio_pin_write(led2, PIN_LED1, leds.led2);
}

void sw3_callback(struct device *sw, struct gpio_callback *cb, u32_t pins)
{
    leds.led3 = ~leds.led3;
    gpio_pin_write(led3, PIN_LED2, leds.led3);
}

void sw4_callback(struct device *sw, struct gpio_callback *cb, u32_t pins)
{
    leds.led4 = ~leds.led4;
    gpio_pin_write(led4, PIN_LED3, leds.led4);
}

// CONNECTING EACH STRUCT DEVICE WITH THE RESPECTIVE PIN AND CONTROLLER ON BOARD
void init_buttons(void)
{
    button1 = device_get_binding(PORT_SW0);
    button2 = device_get_binding(PORT_SW1);
    button3 = device_get_binding(PORT_SW2);
    button4 = device_get_binding(PORT_SW3);

    gpio_pin_configure(button1, PIN_SW0, SW_FLAGS);
    gpio_pin_configure(button2, PIN_SW1, SW_FLAGS);
    gpio_pin_configure(button3, PIN_SW2, SW_FLAGS);
    gpio_pin_configure(button4, PIN_SW3, SW_FLAGS);
}

void init_leds(void)
{
    led1 = device_get_binding(PORT_LED0);
    led2 = device_get_binding(PORT_LED1);
    led3 = device_get_binding(PORT_LED2);
    led4 = device_get_binding(PORT_LED3);

    gpio_pin_configure(led1, PIN_LED0, GPIO_DIR_OUT);
    gpio_pin_configure(led2, PIN_LED1, GPIO_DIR_OUT);
    gpio_pin_configure(led3, PIN_LED2, GPIO_DIR_OUT);
    gpio_pin_configure(led4, PIN_LED3, GPIO_DIR_OUT);
}

// INITIALIZING CALLBACKS AND LINKING EACH ONE WITH THE RESPECTIVE BUTTON
void enable_callbacks(void)
{
    gpio_init_callback(&sw_1, sw1_callback, BIT(PIN_SW0));
    gpio_init_callback(&sw_2, sw2_callback, BIT(PIN_SW1));
    gpio_init_callback(&sw_3, sw3_callback, BIT(PIN_SW2));
    gpio_init_callback(&sw_4, sw4_callback, BIT(PIN_SW3));

    gpio_add_callback(button1, &sw_1);
    gpio_add_callback(button2, &sw_2);
    gpio_add_callback(button3, &sw_3);
    gpio_add_callback(button4, &sw_4);

    gpio_pin_enable_callback(button1, PIN_SW0);
    gpio_pin_enable_callback(button2, PIN_SW1);
    gpio_pin_enable_callback(button3, PIN_SW2);
    gpio_pin_enable_callback(button4, PIN_SW3);
}

void setup(void)
{
    init_buttons();
    init_leds();
    enable_callbacks();
}

void loop(void)
{
    while(1)
    {
        u32_t value = 0U;

        gpio_pin_read(button1, PIN_SW0, &value);
        gpio_pin_read(button2, PIN_SW1, &value);
        gpio_pin_read(button3, PIN_SW2, &value);
        gpio_pin_read(button4, PIN_SW3, &value);

		k_sleep(SLEEP_TIME);
    }  
}

void main(void)
{
    setup();
    loop();
}