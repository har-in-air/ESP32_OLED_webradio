#ifndef PINMODE_H_
#define PINMODE_H_

#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "driver/gpio.h"

#define PIN_OUTPUT 			0
#define PIN_INPUT 			1
#define PIN_INPUT_PULLUP 	2

void pinMode(int pin, int mode);

#endif