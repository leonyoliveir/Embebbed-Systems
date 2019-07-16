/**
 * @file   input.h
 * @author Lucas Peixoto <lucaspeixotoac@gmail.com>
 * @date   Mon Jul  8 08:07:18 2019
 * 
 * @brief  Header file para o driver input
 * 
 * 
 */

#ifndef _INPUT_H_
#define _INPUT_H_

#include <device.h>
#include <gpio.h>

struct input {
    struct device *device;
    struct gpio_callback gpio_callback;
    char *dev_label;
    u32_t pin;
};

typedef struct input input_t;

/** 
 * Essa função tem como objetivo iniciar o device do driver
 * de entrada.
 * @param in 
 *
 * @return 
 */
int input_open(input_t *in, char *dev_label);

/** 
 * Essa função tem como objetivo configurar o pino de entrada.
 *
 * @param in 
 * @param pin 
 * @param flags 
 * @param cb 
 *
 * @return 
 */
int input_configure(input_t *in, u32_t pin, int flags, gpio_callback_handler_t cb);

/** 
 * Essa função tem como objetivo fazer uma leitura do pino
 * de entrada.
 * @param in 
 * @param state 
 *
 * @return 
 */
int input_read(input_t *in, u32_t *state);

/** 
 * Essa função tem como objetivo verificar se o device de
 * entrada foi inicilizado apropriadamente.
 * @param in 
 *
 * @return 
 */
int input_check_error(input_t *in);

/** 
 * Essa função tem como objetivo criar o novo device de entrada
 * fazendo as chamadas padrão de open e configure
 * @param out
 * @param dev_label
 * @param pin
 *
 * @return 
 */
int input_new(input_t *in, char* dev_label, u32_t pin, gpio_callback_handler_t cb);

#endif
