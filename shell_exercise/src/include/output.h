/**
 * @file   output.h
 * @author Lucas Peixoto <lucaspeixotoac@gmail.com>
 * @date   Mon Jul  8 08:04:22 2019
 * 
 * @brief  Header file para o driver output.
 * 
 * 
 */

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <device.h>
#include <gpio.h>

struct output {
    struct device *device;
    char *dev_label;
    u32_t pin;
    u8_t state;
};

typedef struct output output_t;

/** 
 * Essa função tem como objetivo iniciar o driver output,
 * ou seja, iniciar o device. 
 * @param out 
 *
 * @return 
 */
int output_open(output_t *out, char *dev_label);

/** 
 * Essa função tem como objetivo configurar o pino de saída
 * de acordo com suas flags.
 * @param out 
 * @param pin 
 * @param flags 
 *
 * @return 
 */
int output_configure(output_t *out, u32_t pin, int flags);

/** 
 * Essa função tem como objetivo setar o estado do pino de
 * saída para algum valor.
 * @param out 
 * @param value 
 *
 * @return 
 */
int output_set(output_t *out, u8_t value);

/** 
 * Essa função tem como objetivo inverter o estado do pino
 * de saída, de forma digital (0 para 1 e 1 para 0).
 * @param out 
 *
 * @return inverted
 */
int output_digital_invert(output_t *out);

/** 
 * Essa função tem como objetivo verificar se o device de
 * saída foi inicilizado apropriadamente.
 * @param out
 *
 * @return 
 */
int output_check_error(output_t *out);

/** 
 * Essa função tem como objetivo criar o novo device de saída
 * fazendo as chamadas padrão de open e configure
 * @param out
 * @param dev_label
 * @param pin
 *
 * @return 
 */
int output_new(output_t *out, char* dev_label, u32_t pin);
#endif
