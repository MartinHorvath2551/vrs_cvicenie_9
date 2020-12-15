/*
 * hts221.c
 *
 *  Created on: Dec 13, 2020
 *      Author: Martin
 */


#include "i2c.h"
#include <hts221.h>



uint8_t hts221_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, HTS221_ADRESS, 0));
}

void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, HTS221_ADRESS, 1);
}

void hts221_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, HTS221_ADRESS, 0);
}

uint8_t hts221_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = hts221_read_byte(HTS221_WHO_AM_I);

	if(val == HTS221_WHO_AM_I_RESPONSE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		status = 0;
	}


	hts221_write_byte(HTS221_CTRL_REG1, HTS221_CTRL_REG1_SETUP);

	return status;
}



