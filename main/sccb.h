/*
 * This file is part of the OpenMV project.
 * Copyright (c) 2013/2014 Ibrahim Abdelkader <i.abdalkader@gmail.com>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * SCCB (I2C like) driver.
 *
 */
#ifndef __SCCB_H__
#define __SCCB_H__
#include <stdint.h>
int SCCB_Init(int pin_sda, int pin_scl);
uint8_t SCCB_Probe();
uint8_t SCCB_Read(uint8_t slv_addr, uint8_t reg);
uint8_t SCCB_ReadBytes(uint8_t slv_addr, uint8_t reg, uint8_t* pBuf, int numBytes);
uint8_t SCCB_Write(uint8_t slv_addr, uint8_t reg, uint8_t data);
uint8_t SCCB_WriteBytes(uint8_t slv_addr, uint8_t* pBuf, int numBytes);
uint8_t SCCB_Write2(uint8_t slv_addr, uint8_t reg, uint8_t data1, uint8_t data2);
uint8_t SCCB_Write4(uint8_t slv_addr, uint8_t reg, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
#endif // __SCCB_H__
