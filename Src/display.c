/*
 * display.c
 *
 *  Created on: Nov 23, 2020
 *
 */

#include "display.h"
#include "stm32f3xx_it.h"

uint64_t disp_time = 0, disp_time_saved = 0;
extern char string_to_display[];
void updateDisplay(void);
void setDigit(uint8_t pos);

/*Reset (turn-off) all the segments of display*/
void resetSegments(void)
{
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_11);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_8);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_0);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_1);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_3);
}

/*Set (turn-on) all the segments of display*/
void setSegments(void)
{
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_11);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_8);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_1);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_3);
}

/* Reset (turn-off) all digits*/
void resetDigits(void)
{
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_12);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_7);
}

/* Reset (turn-on) all digits*/
void setDigits(void)
{
	DIGIT_1_ON;
	DIGIT_2_ON;
	DIGIT_3_ON;
	DIGIT_4_ON;
	DIGIT_TIME_ON;
}

void setDecimalPoint(void)
{
	LL_GPIO_ResetOutputPin(SEGMENTDP_PORT, SEGMENTDP_PIN);
}

/* Functions to display numbers 0 - 9 */
void set_1(void)
{
	// B,C
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
}

void set_2(void)
{
	// A,B,G,E,D
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
}

void set_3(void)
{
	// A,B,G,C,D
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
}

void set_4(void)
{
	// F,B,G,C
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
}

void set_5(void)
{
	// A,F,G,C,D
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
}

void set_6(void)
{
	// A,F,G,E,C,D
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
}

void set_7(void)
{
	// A,B,C
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
}

void set_8(void)
{
	// A,B,C,D,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
}

void set_9(void)
{
	// A,B,C
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void set_0(void)
{
	// A,B,C,D,E,F
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
}

void set_A(void) {
	// A,B,C,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}


void set_a(void) {
	//1	1	1	1	1	0	1

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_b(void) {
	//0	0	1	1	1	1	1

	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_C(void) {
	//1	0	0	1	1	1	0

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F


}

void set_c(void) {
	//0	0	0	1	1	0	1


	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_d(void) {
	//	0	1	1	1	1	0	1

	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_E(void) {
	//	1	0	0	1	1	1	1

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G
}

void set_F(void) {
	//	1	0	0	0	1	1	1

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_G(void) {
	//	1	0	1	1	1	1	0
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F

}

void set_H(void) {
	//	0	1	1	0	1	1	1

	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_h(void) {
	//	0	0	1	0	1	1	1

	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_I(void) {
	//	0	0	0	0	1	1	0

	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F

}


void set_J(void) {
	//	0	1	1	1	1	0	0

	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E


}

void set_K(void) {
	//

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_L(void) {
	//	0	0	0	1	1	1	0


	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F


}

void set_M(void) {
	//

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B

	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D

	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F

}

void set_n(void) {
	//	0	0	1	0	1	0	1


	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_O(void) {
	//	1	1	1	1	1	1	0

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F

}

void set_o(void) {
	//	0	0	1	1	1	0	1

	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_P(void) {
	//	1	1	0	0	1	1	1

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_q(void) {
	//	1	1	1	0	0	1	1

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_r(void) {
	//	0	0	0	0	1	0	1


	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_S(void) {
	//	1	0	1	1	0	1	1

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_t(void) {
	//	0	0	0	1	1	1	1


	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_U(void) {
	//	0	1	1	1	1	1	0


	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F


}

void set_u(void) {
	//	0	0	1	1	1	0	0


	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E


}

void set_V(void) {
	//


	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B

	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D

	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F


}

void set_W(void) {
	//

	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G


}

void set_X(void) {
	//

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_y(void) {
	//	0	1	1	1	0	1	1

	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN); //C
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN); //F
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G

}

void set_Z(void) {
	//

	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN); //A
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN); //B

	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN); //D
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN); //E

	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN); //G


}


/**
 * Pre-process number before it is displayed. Extract digits of the number
 */
void displayChar(char* message)
{
	for (int i = 0; i < 4; i++){


		switch(i){
		case 3:
			LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2);
			/*LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6);
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);*/
			break;
		case 2:
			LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_12);
			/*LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);*/
			break;
		case 1:
			LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_4);
			/*LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6);
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);*/
			break;
		case 0:
			LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_0);
			/*LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_6);
			LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);*/
			break;
		}




		decode(message[i]);

		resetDigits();
		resetSegments();
	}

}

void decode(char character)
{
	switch(character)
	{
	case 'A':
		set_A();
		break;
	case 'a':
		set_a();
		break;
	case 'b':
	case 'B':
		set_b();
		break;
	case 'C':
		set_C();
		break;
	case 'c':
		set_c();
		break;
	case 'd':
	case 'D':
		set_d();
		break;
	case 'E':
	case 'e':
		set_E();
		break;
	case 'F':
	case 'f':
		set_F();
		break;
	case 'G':
	case 'g':
		set_G();
		break;
	case 'H':
		set_H();
		break;
	case 'h':
		set_h();
		break;
	case 'I':
	case 'i':
		set_I();
		break;
	case 'J':
	case 'j':
		set_J();
		break;
	case 'K':
	case 'k':
		set_K();
		break;
	case 'L':
	case 'l':
		set_L();
		break;
	case 'M':
	case 'm':
		set_M();
		break;
	case 'n':
	case 'N':
		set_n();
		break;
	case 'O':
		set_O();
		break;
	case 'o':
		set_o();
		break;
	case 'P':
	case 'p':
		set_P();
		break;
	case 'q':
	case 'Q':
		set_q();
		break;
	case 'r':
	case 'R':
		set_r();
		break;
	case 'S':
	case 's':
		set_S();
		break;
	case 't':
	case 'T':
		set_t();
		break;
	case 'U':
		set_U();
		break;
	case 'u':
		set_u();
		break;
	case 'V':
	case 'v':
		set_V();
		break;
	case 'W':
	case 'w':
		set_W();
		break;
	case 'X':
	case 'x':
		set_X();
		break;
	case 'y':
	case 'Y':
		set_y();
		break;
	case 'Z':
	case 'z':
		set_Z();
		break;
	case '1':
		set_1();
		break;
	case '2':
		set_2();
		break;
	case '3':
		set_3();
		break;
	case '4':
		set_4();
		break;
	case '5':
		set_5();
		break;
	case '6':
		set_6();
		break;
	case '7':
		set_7();
		break;
	case '8':
		set_8();
		break;
	case '9':
		set_9();
		break;
	case '0':
		set_0();
		break;

	}

}







