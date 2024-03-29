#define PORT_LED0       LED0_GPIO_CONTROLLER
#define PORT_LED1       LED1_GPIO_CONTROLLER
#define PORT_LED2       LED2_GPIO_CONTROLLER
#define PORT_LED3       LED3_GPIO_CONTROLLER
#define PIN_LED0        LED0_GPIO_PIN
#define PIN_LED1        LED1_GPIO_PIN
#define PIN_LED2        LED2_GPIO_PIN
#define PIN_LED3        LED3_GPIO_PIN

#define PORT_SW0	      SW0_GPIO_CONTROLLER
#define PORT_SW1        SW1_GPIO_CONTROLLER
#define PORT_SW2        SW2_GPIO_CONTROLLER
#define PORT_SW3        SW3_GPIO_CONTROLLER
#define PIN_SW0         SW0_GPIO_PIN
#define PIN_SW1         SW1_GPIO_PIN
#define PIN_SW2         SW2_GPIO_PIN
#define PIN_SW3         SW3_GPIO_PIN

#define INTERRUPT       GPIO_INT
#define FALL_EDGE       (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#define DEBOUNCE        GPIO_INT_DEBOUNCE
#define PULL_UP         GPIO_PUD_PULL_UP
#define INPUT_FLAGS     (GPIO_DIR_IN | INTERRUPT | FALL_EDGE | DEBOUNCE | PULL_UP)
#define OUTPUT_FLAGS    GPIO_DIR_OUT
#define SLEEP_TIME      500
