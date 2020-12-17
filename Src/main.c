/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"
#include "display.h"
#include <string.h>
#include "math.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lsm6ds0.h"
#include "hts221.h"
#include "lps25hb.h"
#include "lis3mdltr.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t temp = 0;
float mag[3], acc[3];

float temperature = 0;
float humidity = 0;
float pressure = 0;
float azimuth = 0;
float altitude = 0;


extern uint64_t disp_time;
//char string[]= "MARTINHORVATH92601";
char string[]= "   123456789   ";
char string_to_display[5]= "";
char empty_string[]=" ";
uint64_t saved_time;
int switch_state=1;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//lsm6ds0_init();
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();

  /* USER CODE BEGIN 2 */

  setSegments();
  setDigits();
  LL_mDelay(2000);
  resetDigits();
  resetSegments();
  lsm6ds0_init();

  hts221_init();
  lis3mdl_init();
  lps25hb_init();



  MX_TIM2_Init();
  /* USER CODE END 2 */
  int shift=0;
  int index=0;
  int direction=1;
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  /*
	  	  lsm6ds0_get_acc(acc, (acc+1), (acc+2));
	  	  LL_mDelay(50);
	  	  */

	  	  humidity = hts221_get_humidity();
	  	  temperature = hts221_get_temperature();
		  pressure = lps25hb_get_pressure();
		  azimuth = lis3mdl_get_azimuth();
		  altitude = get_altitude();


		  index=shift;

		  LL_mDelay(500);

		  if(direction==1)
		  {


			  for(int i = 0; i < 4; i++){

				 /* if(index+i>=(strlen(string))){
					  string_to_display[i]=empty_string[0];

				  }
				  else
				  {
					  string_to_display[i]=string[index+i];
				  }*/

				  string_to_display[i]=string[index+i];



			  }

			  if(shift<(strlen(string)-4)){
				  shift++;
			  }
			  else
			  {

				  direction=0;
			  }
		  }
		  else
		  {

			  for(int i = 0; i < 4; i++)
			  {

				  /*if(index+i>=(strlen(string))){
					  string_to_display[i]=empty_string[0];

				  }
				  else
				  {
					  string_to_display[i]=string[index+i];
				  }*/

				  string_to_display[i]=string[index+i];
			  }

			  if(shift!=0){
				  shift--;
			  }
			  else
			  {

				  direction=1;
			  }

		  }

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(8000000);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
  LL_SYSTICK_EnableIT();
}

/* USER CODE BEGIN 4 */


float get_altitude()
{
	//https://keisan.casio.com/exec/system/1224585971

	float pressure_alt = lps25hb_get_pressure();
	float temperature_alt = hts221_get_temperature();
	float altitude_alt;

	altitude_alt = ((powf((1013.25/pressure_alt),1/5.257)-1)*(temperature_alt+273.15))/0.0065;

	return altitude_alt;
}





/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
