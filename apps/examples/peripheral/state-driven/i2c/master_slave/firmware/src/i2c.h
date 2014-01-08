/* 
 * File:   i2c.h
 * Author: C15287
 *
 * Created on August 12, 2013, 2:32 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <stdbool.h>

void LEDIndicateWorking(void);
bool masterTransferIsComplete(void);
void initMaster(int baudRate, int clockFrequency);
void initSlave(int baudRate, int clockFrequency, int address);
char SlaveRead(void);

#endif	/* I2C_H */

