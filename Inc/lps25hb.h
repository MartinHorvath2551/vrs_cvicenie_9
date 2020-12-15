/*
 * lps25hb.h
 *
 *  Created on: Dec 15, 2020
 *      Author: Martin
 */

#ifndef LPS25HB_H_
#define LPS25HB_H_


#define 	LPS25HB_STATUS_REG					0x27
#define 	LPS25HB_WHO_AM_I					0x0F
#define 	LPS25HB_WHO_AM_I_RESPONSE			0xBD
#define 	LPS25HB_CTRL_REG1					0x20
#define 	LPS25HB_CTRL_REG1_SETUP				0x90
#define 	LPS25HB_ADDRESS						0xBB




uint8_t lps25hb_init(void);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);
void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length);
uint8_t lps25hb_read_byte(uint8_t reg_addr);
float lps25hb_get_pressure();

#endif /* LPS25HB_H_ */
