/*
 * lps25hb.c
 *
 *  Created on: Dec 15, 2020
 *      Author: Martin
 */

#include "i2c.h"
#include <lps25hb.h>



uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, LPS25HB_ADDRESS, 0));
}

void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, LPS25HB_ADDRESS, 1);
}

void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, LPS25HB_ADDRESS, 0);
}

uint8_t lps25hb_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = lps25hb_read_byte(LPS25HB_WHO_AM_I);

	if(val == LPS25HB_WHO_AM_I_RESPONSE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		status = 0;
	}

	//acc device init

	lps25hb_write_byte(LPS25HB_CTRL_REG1, LPS25HB_CTRL_REG1_SETUP);


	return status;
}

float lps25hb_get_pressure(){

	uint8_t h, xl, l;

	h = lps25hb_read_byte(0x2A);
	xl = lps25hb_read_byte(0x28);
	l = lps25hb_read_byte(0x29);

	float pressure = (h << 16 | l << 8 | xl)/4096;

	return pressure;
}
