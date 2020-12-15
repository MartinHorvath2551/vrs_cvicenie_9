/*
 * hts221.h
 *
 *  Created on: Dec 15, 2020
 *      Author: Martin
 */

#ifndef HTS221_H_
#define HTS221_H_


#define 	HTS221_STATUS_REG					0x27
#define 	HTS221_WHO_AM_I						0x0F
#define 	HTS221_WHO_AM_I_RESPONSE			0xBC
#define 	HTS221_CTRL_REG1					0x20
#define 	HTS221_CTRL_REG1_SETUP				0x81
#define 	HTS221_ADRESS						0xbe
#define 	HTS221_DEVICE_ON					1000001


uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length);
uint8_t hts221_init(void);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);

#endif /* HTS221_H_ */




