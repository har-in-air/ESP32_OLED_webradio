#include "common.h"
#include "config.h"
#include "myi2c.h"
#include "pinmode.h"
#include "tas5753md.h"

#define TAG "TAS5753"

void tas5753_Config(void) {
   uint8_t regbuf[4];
   uint8_t regRead;
   
   i2c_WriteRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_OSC_TRIM, 0x00); 
   delayMs(500);
   i2c_ReadRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_OSC_TRIM, &regRead);
   ESP_LOGI(TAG,"TAS : Osc Trim = %02X", regRead);   

   i2c_WriteRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_SDATA_INTERFACE, 0x03); // i2s 16bit

   //i2c_ReadBuffer(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_BANK_SW_CTRL, regbuf, 4);
   //ESP_LOGI(TAG,"TAS : Bank Switch Control = %02X %02x %02x %02X", regbuf[0],regbuf[1],regbuf[2],regbuf[3] );   

   uint8_t bankswctrl[] = {TAS5753MD_REG_BANK_SW_CTRL, regbuf[0], regbuf[1], regbuf[2], regbuf[3] | 0x80}; // disable equalizer
   i2c_WriteCommands(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, bankswctrl, 5);

   //i2c_ReadBuffer(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_BANK_SW_CTRL, regbuf, 4);
   //ESP_LOGI(TAG,"TAS : Bank Switch Control = %02X %02X %02X %02X", regbuf[0],regbuf[1],regbuf[2],regbuf[3] );   
   
   i2c_ReadRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_SDATA_INTERFACE, &regRead);
   ESP_LOGI(TAG,"TAS : Serial Data Interface = %02X", regRead);   
   i2c_ReadRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_CLOCK_CTRL, &regRead);
   ESP_LOGI(TAG,"TAS : Clock Control = %02X", regRead);   
   
   i2c_ReadRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_PWM_SHUTDOWN, &regRead);
   ESP_LOGI(TAG,"TAS : PWM Shutdown Group = %02X", regRead);   
   
   i2c_ReadRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_SOFT_MUTE, &regRead);
   ESP_LOGI(TAG,"TAS : Soft Mute = %02X", regRead);   
   
   i2c_ReadBuffer(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_INPUT_MUX, regbuf, 4);
   ESP_LOGI(TAG,"TAS : Input Mux = %02X %02X %02X %02X", regbuf[0],regbuf[1],regbuf[2],regbuf[3] );   
   
   i2c_ReadBuffer(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_PWM_MUX, regbuf, 4);
   ESP_LOGI(TAG,"TAS : PWM Mux = %02X %02X %02X %02X", regbuf[0],regbuf[1],regbuf[2],regbuf[3] );   
      
   // exit shutdown
   i2c_WriteRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_SYS_CTRL_2, 0x00); 
   delayMs(100);
   //i2c_ReadRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_SYS_CTRL_2, &regRead);
   //ESP_LOGI(TAG,"TAS : System Control 2 = %02X", regRead);   

   uint8_t mastervol[] = {TAS5753MD_REG_MASTER_VOL, 0x01, 0x40};
   i2c_WriteCommands(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, mastervol, 3); 


   i2c_ReadBuffer(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_MASTER_VOL, regbuf, 2);
   ESP_LOGI(TAG, "TAS : Master Vol = %02X %02X", regbuf[0],regbuf[1] );   
   //i2c_ReadBuffer(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_CHAN1_VOL, regbuf, 2);
   //ESP_LOGI(TAG,"TAS : Chan1 Vol = %02X %02X\r\n", regbuf[0],regbuf[1] );   
   //i2c_ReadBuffer(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_CHAN2_VOL, regbuf, 2);
   //ESP_LOGI(TAG,"TAS : Chan2 Vol = %02X %02X\r\n", regbuf[0],regbuf[1] );   
   //i2c_ReadBuffer(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_CHAN3_VOL, regbuf, 2);
   //ESP_LOGI(TAG,"TAS : Chan3 Vol = %02X %02X\r\n", regbuf[0],regbuf[1] );   

   i2c_WriteRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_ERROR_STATUS, 0x00); // clear errors
   delayMs(100);
   i2c_ReadRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, TAS5753MD_REG_ERROR_STATUS, &regRead);   
   ESP_LOGI(TAG, "TAS : Error Status = %02X",regRead);
	}
	


esp_err_t tas5753_Reset(void) {
	pinMode(pinSW, PIN_OUTPUT);
	gpio_set_level(pinSW, 0);
	pinMode(pinRST, PIN_OUTPUT);
	gpio_set_level(pinRST, 1);
	pinMode(pinPDN, PIN_OUTPUT);
	gpio_set_level(pinPDN, 0);
	delayMs(100);
	gpio_set_level(pinSW, 1); // switch on PVDD
	delayMs(100);

	gpio_set_level(pinPDN, 1);
	delayMs(100);
	gpio_set_level(pinRST, 0); // pulse reset pin
	delayMs(1); // min 0.1mS
	gpio_set_level(pinRST, 1);
	delayMs(20); // min 13.5mS
	
	uint8_t deviceID;	
    esp_err_t ret =	i2c_ReadRegister(I2C_MASTER_NUM, TAS5753MD_I2C_ADDR, 0x01, &deviceID);
	if (ret == ESP_FAIL) {
		ESP_LOGE(TAG,"i2cread tas5753md failed");
		}
	else {
		ESP_LOGE(TAG,"TAS5753MD DEVICE ID [expected 0x41] = 0x%02X", deviceID); 
		}
	return ret;
	}
	