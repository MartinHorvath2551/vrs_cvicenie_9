/*
 * display.c
 *
 *  Created on: Nov 23, 2020
 *      Author: Stancoj
 */

#include "main.h"
#include <stdio.h>
#include <string.h>

#define SEGMENTA_PIN	LL_GPIO_PIN_1
#define SEGMENTA_PORT	GPIOA

#define SEGMENTB_PIN	LL_GPIO_PIN_0
#define SEGMENTB_PORT	GPIOA

#define SEGMENTC_PIN	LL_GPIO_PIN_8
#define SEGMENTC_PORT	GPIOA

#define SEGMENTD_PIN	LL_GPIO_PIN_5
#define SEGMENTD_PORT	GPIOB

#define SEGMENTE_PIN 	LL_GPIO_PIN_11
#define SEGMENTE_PORT	GPIOA

#define SEGMENTF_PIN 	LL_GPIO_PIN_3
#define SEGMENTF_PORT	GPIOA

#define SEGMENTG_PIN	LL_GPIO_PIN_4
#define SEGMENTG_PORT	GPIOB

#define SEGMENTDP_PIN	LL_GPIO_PIN_1
#define SEGMENTDP_PORT	GPIOB

#define DIGIT_1_ON		LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_0)
#define DIGIT_2_ON		LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_4)
#define DIGIT_3_ON		LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_12)
#define DIGIT_4_ON		LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2)
#define DIGIT_TIME_ON	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_7)



void resetDigits(void);
void setDigits(void);
void resetSegments(void);
void setSegments(void);

void setDecimalPoint(void);

void displayChar(char* message);
void decode(char character);
void printChar(unsigned short message,int digit);

void set_1(void);

void set_2(void);

void set_3(void);

void set_4(void);

void set_5(void);

void set_6(void);

void set_7(void);

void set_8(void);

void set_9(void);

void set_0(void);

void set_A(void);


void set_a(void);

void set_b(void);

void set_C(void);

void set_c(void);

void set_d(void);

void set_E(void);

void set_F(void);

void set_G(void);

void set_H(void);

void set_h(void);

void set_I(void);


void set_J(void);

void set_K(void);

void set_L(void);

void set_M(void);

void set_n(void);

void set_O(void);

void set_o(void);

void set_P(void);

void set_q(void);
void set_r(void);

void set_S(void);

void set_t(void);

void set_U(void);

void set_u(void);

void set_V(void);

void set_W(void);

void set_X(void);

void set_y(void);

void set_Z(void);

void set__(void);

void set_space(void);

