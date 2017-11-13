#include "common.h"
#include "pinmode.h"


void pinMode(int pin, int mode) {
    gpio_config_t conf = {0};
    conf.pin_bit_mask = 1LL << pin;
	if (mode == PIN_OUTPUT) {
		conf.mode = GPIO_MODE_OUTPUT;
		}
	if (mode == PIN_INPUT || mode == PIN_INPUT_PULLUP) {
	    conf.mode = GPIO_MODE_INPUT;
		}
	if (mode == PIN_INPUT) {
	    conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
	    conf.pull_up_en = GPIO_PULLUP_DISABLE;
		}
	else if (mode == PIN_INPUT_PULLUP) {
        conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
        conf.pull_up_en = GPIO_PULLUP_ENABLE;
		}
	gpio_config(&conf);
	}
