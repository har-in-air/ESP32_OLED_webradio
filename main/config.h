#ifndef CONFIG_H_
#define CONFIG_H_

#include "driver/i2c.h"

#define I2C_MASTER_SCL_IO    		14
#define I2C_MASTER_SDA_IO    		13
#define I2C_MASTER_NUM 				I2C_NUM_1   
#define I2C_MASTER_TX_BUF_DISABLE   0   
#define I2C_MASTER_RX_BUF_DISABLE   0   
#define I2C_MASTER_FREQ_HZ    		100000 

#define pinRST		33
#define pinPDN		4
#define pinSW		32
#define pinLED		5

#endif
