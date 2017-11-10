#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <nvs.h>


#include "esp_system.h"
#include "esp_log.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#define delayMs(ms)  vTaskDelay((ms) / portTICK_PERIOD_MS);

#define ABS(x) ((x) < 0 ? -(x) : (x))


#endif