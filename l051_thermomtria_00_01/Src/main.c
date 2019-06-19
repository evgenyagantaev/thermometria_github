/**
******************************************************************************
* File Name          : main.c
* Description        : Main program body
******************************************************************************
*
* COPYRIGHT(c) 2016 STMicroelectronics
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/
// Includes ------------------------------------------------------------------
#include "stm32l0xx_hal.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "string.h"
#include <math.h>
#include <errno.h>



// Private constants ---------------------------------------------------------
const GPIO_TypeDef *port[] = {GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA, GPIOA,
				                      GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB};
const uint16_t pin[] = {GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12,
						GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11};

const uint16_t TON1_TON4_pin[] = {GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_3, GPIO_PIN_4};

const double A = 0.0014733;
const double B = 0.0002372;
const double C = 1.074e-07;
const double a = -7.858e-06;
const double b = -1.778e-01;
const double c = 2.0464e+02;

// Private variables ---------------------------------------------------------
int debug_flag = 0;
UART_HandleTypeDef huart1;
uint8_t message[128];

int32_t buffer0[34];
int32_t buffer1[34];
int16_t aux16;
uint8_t aux8;


#define FLUX		// if defined, thermo fluxes are calculated and output

#include "calibration_table_001.h"

double surface_themps[2][16];

int32_t *out_buffer = buffer0;
int32_t *fill_buffer = buffer1;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

// Private function prototypes -----------------------------------------------
void SystemClock_Config(void);
void reset_ads1220_1(uint8_t input);
void reset_ads1220_2(uint8_t input);
int readConfiguration_ads1220_1(void);
int readConfiguration_ads1220_2(void);
uint32_t read_adc1(void);
uint32_t read_adc2(void);
int *_errno(void);


void short_delay()
{
    volatile int i;

    // test delay
    for(i=0; i<5; i++)
    {
	    i++;
	    i--;
    }
}

void long_delay()
{
    volatile long i;

    // test delay
    for(i=0; i<500000; i++)
    {
	    i++;
	    i--;
    }
}





	// end configure data
	//************************************************************


// Private functions prototypes -----------------------------------------------

//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************

int main(void)
{

	uint8_t i,j,k;

	// MCU Configuration----------------------------------------------------------

	// Reset of all peripherals, Initializes the Flash interface and the Systick.
	HAL_Init();

	// Configure the system clock
	SystemClock_Config();

	// Initialize all configured peripherals
	MX_GPIO_Init();
	MX_SPI1_Init();
	// enable spi1
	SPI1->CR1 |= SPI_CR1_SPE;
	MX_SPI2_Init();
	SPI2->CR2 &= ~SPI_CR2_TXEIE;   // disable txe interrupt
	SPI2->CR2 &= ~SPI_CR2_ERRIE;   // disable error interrupt
	SPI2->CR2 |= SPI_CR2_RXNEIE;   // enable rxne interrupt
	// enable spi2
	SPI2->CR1 |= SPI_CR1_SPE;
	MX_TIM2_Init();
	MX_USART1_UART_Init();

	readConfiguration_ads1220_1();
	readConfiguration_ads1220_2();
	//***********************************************

	uint32_t adc_data = 0;

	int counter = 0;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET); // turn on thermosensors

	/*
	reset_ads1220_2(0x01); // configure adc2 input 1
	HAL_GPIO_WritePin(port[2], pin[2], GPIO_PIN_SET); // turn on thermosensor i
	while (1)
	{

		HAL_Delay(3);
		adc_data = read_adc2();
		double adc2_input_voltage = ((double)adc_data) / ((double)(8388608.0 / 2048.0));
		double V = adc2_input_voltage;
		double adc2_themperature_1 = a*V*V + b*V + c;
		surface_themps[0][2] = adc2_themperature_1;
		double t = adc2_themperature_1 *100.0;
		fill_buffer[2] = (int32_t)(t - (p[2]*t + q[2]));
		//fill_buffer[i] = adc_data;

		// change buffers
		int32_t *aux_pointer = out_buffer;
		out_buffer = fill_buffer;
		fill_buffer = aux_pointer;

	}
	*/

	// set up calibration data:
	/*
	for(i=0; i<DATA_LENGTH; i++)
	{
		D[i] = L[i] - H[i];
		Q[i] = D[i]/(T0+500);		// correction on -5 Celsius
	}
	*/

	while (1)
	{



		// calibrate adc1 (vhod ain1) *****************************
		reset_ads1220_1(0x01); // configure adc1 input 1
		HAL_Delay(3);
		adc_data = read_adc1();
		double range = 8388608.0;
		double range_offset = ((double)adc_data)*3300.0/(2200.0/4.0) - range; // tok 250 uA, soprotivlenie 2200 Ohm
		range += range_offset;
		//double adc1_reference_voltage = ((double)adc_data) / ((double)(8388608 / 2048));
		double adc1_reference_voltage = ((double)adc_data) / ((double)(range / 3300.0));
		//sprintf(message, "%f\r\n", adc1_reference_voltage);
		//HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);
		//const double internal_reference = 2048.0 + (double)((1100.0 - adc1_reference_voltage) * 8388608.0 / ((double)adc_data));
		//const double internal_reference = 3300.0 + (double)((2200.0 - adc1_reference_voltage) * 8388608.0 / ((double)adc_data));

		// read oral temperature (adc1 vhod ain2)
		reset_ads1220_1(0x02); // configure adc1 input 2
		HAL_Delay(3);
		adc_data = read_adc1();

		double oral_voltage = ((double)adc_data) / ((double)(range / 3300));
		//double oral_rezistance = oral_voltage * 2;
		double oral_rezistance = oral_voltage * 4.0;
		double LnR = log(oral_rezistance);
		double oral_temperature = A + B * LnR + C * LnR * LnR * LnR;
		oral_temperature = 1.0 / oral_temperature;
		oral_temperature -= 273.15;
		double t = oral_temperature * 100.0;
		fill_buffer[DATA_LENGTH - 2] = (int32_t)t;
		if(t >= T0)
			fill_buffer[DATA_LENGTH - 2] = (int32_t)(t - H[DATA_LENGTH - 2]);
		else // t < T0
			fill_buffer[DATA_LENGTH - 2] = (int32_t)(t -(H[DATA_LENGTH - 2] + (T0-t)*Q[DATA_LENGTH - 2]));

		reset_ads1220_1(0x03); // configure adc1 input 3
		HAL_Delay(3);
		adc_data = read_adc1();
		double rectal_voltage = ((double)adc_data) / ((double)(range / 3300));

		double rectal_rezistance = rectal_voltage * 4.0;
		LnR = log(rectal_rezistance);
		double rectal_temperature = A + B * LnR + C * LnR * LnR * LnR;
		rectal_temperature = 1.0 / rectal_temperature;
		rectal_temperature -= 273.15;
		t = rectal_temperature * 100.0;
		fill_buffer[DATA_LENGTH - 1] = (int32_t)t;
		if(t >= T0)
			fill_buffer[DATA_LENGTH - 1] = (int32_t)(t - H[DATA_LENGTH - 1]);
		else // t < T0
			fill_buffer[DATA_LENGTH - 1] = (int32_t)(t -(H[DATA_LENGTH - 1] + (T0-t)*Q[DATA_LENGTH - 1]));


		//read surface themperatures and fluxes ************************************



		//----------------------------------------------------------------------------


		reset_ads1220_2(0x01); // configure adc2 input 1

		for (i = 0; i < 16; i++)
		{
			//HAL_GPIO_WritePin(port[i], pin[i], GPIO_PIN_SET); // turn on thermosensor i
			uint8_t TON1_TON4_index;
			TON1_TON4_index = (i & (~0x0c));
			HAL_GPIO_WritePin(GPIOA, TON1_TON4_pin[TON1_TON4_index], GPIO_PIN_SET); // turn on thermosensor
			if(i >> 3)
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); // turn on S1
			if((i & (~0x08)) >> 2)
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // turn on S0
			HAL_Delay(3);
			adc_data = read_adc2();
			double adc2_input_voltage = ((double)adc_data) / ((double)(8388608.0 / 2048.0));
			double V = adc2_input_voltage;
			double adc2_themperature_1 = a*V*V + b*V + c;
			surface_themps[0][i] = adc2_themperature_1;
			t = adc2_themperature_1 *100.0;
			fill_buffer[i] = (int32_t)t;

			HAL_GPIO_WritePin(GPIOA, TON1_TON4_pin[TON1_TON4_index], GPIO_PIN_RESET); // turn off thermosensor
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); // turn off S1
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); // turn off S0
			HAL_Delay(3);

		}
		reset_ads1220_2(0x00); // configure adc2 input 0

		for (i = 0; i < 16; i++)
		{
			//HAL_GPIO_WritePin(port[i], pin[i], GPIO_PIN_SET); // turn on thermosensor i
			uint8_t TON1_TON4_index;
			TON1_TON4_index = (i & (~0x0c));
			HAL_GPIO_WritePin(GPIOA, TON1_TON4_pin[TON1_TON4_index], GPIO_PIN_SET); // turn on thermosensor
			if(i >> 3)
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); // turn on S1
			if((i & (~0x08)) >> 2)
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET); // turn on S0
			HAL_Delay(3);
			HAL_Delay(3);
			adc_data = read_adc2();
			double adc2_input_voltage = ((double)adc_data) / ((double)(8388608.0 / 2048.0));
			double V = adc2_input_voltage;
			double adc2_themperature_2 = a*V*V + b*V + c;
			surface_themps[1][i] = adc2_themperature_2;
			t = adc2_themperature_2 *100.0;
			fill_buffer[16 + i] = (int32_t)t;

			//HAL_GPIO_WritePin(port[i], pin[i], GPIO_PIN_RESET); // turn off thermosensor i
			HAL_GPIO_WritePin(GPIOA, TON1_TON4_pin[TON1_TON4_index], GPIO_PIN_RESET); // turn off thermosensor
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); // turn off S1
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); // turn off S0
			HAL_Delay(3);
		}

		// calibrate
		for (i = 0; i < (DATA_LENGTH-2); i++)
		{
			if(fill_buffer[i] >= T0)
			{
				fill_buffer[i] = (int32_t)(fill_buffer[i] - H[i]); // O4-($X4+(O4-$X4-20)*0.032)
				//fill_buffer[i] = (int32_t)(fill_buffer[i] - (H[i] + (fill_buffer[i] - H[i] - T1)*0.032));
			}
			else // t < T0
				fill_buffer[i] = (int32_t)(fill_buffer[i] -(H[i] + (T0-fill_buffer[i])*Q[i]));
		}


#ifdef FLUX	//*****************************************************************************
		for (i = 0; i < (DATA_LENGTH-2)/2; i++)
		{

			fill_buffer[16 + i] = (fill_buffer[i] - fill_buffer[16 + i]) * K[i] - J[i];
		}
#endif		//*****************************************************************************

		// change buffers
		int32_t *aux_pointer = out_buffer;
		out_buffer = fill_buffer;
		fill_buffer = aux_pointer;

		//HAL_GPIO_TogglePin(led0_GPIO_Port, led0_Pin);
		//HAL_Delay(500);

		/*
		sprintf(message, "*****************************************************\r\n", hx, hy, hz);
		HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);
		sprintf(message, "%d   %d   %d\r\n", hx, hy, hz);
		HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);
		sprintf(message, "%d   %d   %d\r\n", accel_x, accel_y, accel_z);
		HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);
		sprintf(message, "%d   %d   %d\r\n", gyro_x, gyro_y, gyro_z);
		HAL_UART_Transmit(&huart1, message, strlen((const char *)message), 500);
		//*/

		//***********************************************************

	}// end while


}// end main

//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************

/// System Clock Configuration

void SystemClock_Config(void)
{

RCC_OscInitTypeDef RCC_OscInitStruct;
RCC_ClkInitTypeDef RCC_ClkInitStruct;
RCC_PeriphCLKInitTypeDef PeriphClkInit;

__PWR_CLK_ENABLE();

__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
RCC_OscInitStruct.HSIState = RCC_HSI_ON;
RCC_OscInitStruct.HSICalibrationValue = 16;
RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
HAL_RCC_OscConfig(&RCC_OscInitStruct);

RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

// SysTick_IRQn interrupt configuration
HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

// USER CODE BEGIN 4

// USER CODE END 4

#ifdef USE_FULL_ASSERT

/**
* @brief Reports the name of the source file and the source line number
* where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
// USER CODE BEGIN 6 */
/* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
// USER CODE END 6 */

}

#endif


// Function resets ads1220 �1 (oral+rectal; )
void reset_ads1220_1(uint8_t input)
{
   uint8_t aux;

   HAL_GPIO_WritePin(GPIOH, GPIO_PIN_0, GPIO_PIN_RESET); // open spi communication adc1

   if ((SPI1->SR & SPI_FLAG_RXNE) != RESET )
	aux=SPI1->DR;

   // write RESET command (0x06)
   while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
   SPI1->DR=0x06;
   // fictious reading
   while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
   aux = SPI1->DR;


	volatile long i;
	for(i=0; i<1500000; i++);


  // *** configure configuration register:
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  SPI1->DR=0x43;    // WREG 4 registers starting from address 00
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;


  // write in the configuration registers
  uint8_t conf00reg = ((0x08 | input)<<4) + 0x01;  //[10xx] + ainx; - avss; [000] gain 1; [1] pga disabled; [10010001]
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  SPI1->DR=conf00reg;
  //SPI1->DR=0xe1;  //[1110] +&- (avss+avdd)/2; [000] gain 1; [1] pga disabled; [11100001]
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  SPI1->DR=0x80;    // [100] 330 sps (normal mode); [00] normal mode; [0] single-shot; [0]; [0]; [10000000]
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  //SPI1->DR=0x05;    // [00] internal 2.048V ref; [00] no filters; [0]; [101] 500 uA current source [00000101]
  //SPI1->DR=0xc6;    // [11] avdd 3.3V ref; [00] no filters; [0]; [110] 1000 uA current source [11000110]
  SPI1->DR=0xc4;    // [11] avdd 3.3V ref; [00] no filters; [0]; [100] 250 uA current source [11000100]
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;
  uint8_t conf03reg = (input + 1)<<5; // [xxx] idac1 connected to ainx; [000] idac2 disabled; [0] drdy pin used; [xxx00000]
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  SPI1->DR=conf03reg;
  //SPI1->DR=0x00;    // [000] idac1 disabled; [000] idac2 disabled; [0] drdy pin used; [00000000]
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;

  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_0, GPIO_PIN_SET); // close spi communication adc1


}//end reset_ads1220_1

// Function resets ads1220 �2
void reset_ads1220_2(uint8_t input)
{
   uint8_t aux;

   HAL_GPIO_WritePin(GPIOH, GPIO_PIN_1, GPIO_PIN_RESET); // open spi communication adc2

   if ((SPI1->SR & SPI_FLAG_RXNE) != RESET )
	aux=SPI1->DR;

   // write RESET command (0x06)
   while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
   SPI1->DR=0x06;
   // fictious reading
   while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
   aux = SPI1->DR;


	volatile long i;
	for(i=0; i<1500000; i++);


  // *** configure configuration register:
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  SPI1->DR=0x43;    // WREG 4 registers starting from address 00
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;

  uint8_t conf00reg = ((0x08 | input)<<4) + 0x01;  //[10xx] + ainx; - avss; [000] gain 1; [1] pga disabled; [10010001]
  //uint8_t conf00reg = 0xe1;  //[1110] shorted to (avdd + avss)/2; [000] gain 1; [1] pga disabled; [10010001]
  //uint8_t conf00reg = 0xd1;  //[1101] (avdd - avss)/4 monitor; [000] gain 1; [1] pga disabled; [10010001]

  // write in the configuration registers
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  SPI1->DR=conf00reg;
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  //SPI1->DR=0xc4;    // [110] 1000 sps (normal mode); [00] normal mode; [1] continuous conversion; [0]; [0]; [11000100]
  SPI1->DR=0x84;    // [100] 330 sps (normal mode); [00] normal mode; [1] continuous conversion; [0]; [0]; [10000100]
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  //SPI1->DR=0x00;    // [00] internal 2.048V ref; [00] no filters; [0]; [000] current off [00000000]
  SPI1->DR=0x40;    // [01] external 2.048V ref; [00] no filters; [0]; [000] current off [00000000]
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;
  while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
  SPI1->DR=0x00;    // [000] idac1 disabled; [000] idac2 disabled; [0] drdy pin used; [00000000]
  // fictious reading
  while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
  aux = SPI1->DR;

  HAL_GPIO_WritePin(GPIOH, GPIO_PIN_1, GPIO_PIN_SET); // close spi communication adc2


}//end reset_ads1220_2


// Function reads and checks id register (adc1)
int readConfiguration_ads1220_1(void)
{
	static uint8_t aux;

	static volatile uint8_t configuration[4];

	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_0, GPIO_PIN_RESET); // open spi communication adc1

	if ((SPI1->SR & SPI_FLAG_RXNE) != RESET )
	aux=SPI1->DR;

	// send read configuration registers command:
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	SPI1->DR=0x23;    // RREG 4 registers starting from address 00
	// fictious reading
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	aux = SPI1->DR;

	// read registers
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	// fictious write in spi (just to start a clock and read data
	SPI1->DR=0x00;
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	configuration[0]=SPI1->DR;
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	// fictious write in spi (just to start a clock and read data
	SPI1->DR=0x00;
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	configuration[1]=SPI1->DR;
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	// fictious write in spi (just to start a clock and read data
	SPI1->DR=0x00;
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	configuration[2]=SPI1->DR;
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	// fictious write in spi (just to start a clock and read data
	SPI1->DR=0x00;
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	configuration[3]=SPI1->DR;

	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_0, GPIO_PIN_SET); // close spi communication adc1

	// check the value
	if(configuration[0] == 0x64 && configuration[1] == 0x94) // we have got a correct interface
	 return 0; // ok
	else
	 return 1; // id
}//end readConfiguration_ads1220_1

// Function reads and checks id register (adc2)
int readConfiguration_ads1220_2(void)
{
	static uint8_t aux;

	static volatile uint8_t configuration[4];

	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_1, GPIO_PIN_RESET); // open spi communication adc2

	if ((SPI1->SR & SPI_FLAG_RXNE) != RESET )
	aux=SPI1->DR;

	// send read configuration registers command:
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	SPI1->DR=0x23;    // RREG 4 registers starting from address 00
	// fictious reading
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	aux = SPI1->DR;

	// read registers
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	// fictious write in spi (just to start a clock and read data
	SPI1->DR=0x00;
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	configuration[0]=SPI1->DR;
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	// fictious write in spi (just to start a clock and read data
	SPI1->DR=0x00;
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	configuration[1]=SPI1->DR;
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	// fictious write in spi (just to start a clock and read data
	SPI1->DR=0x00;
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	configuration[2]=SPI1->DR;
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	// fictious write in spi (just to start a clock and read data
	SPI1->DR=0x00;
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	configuration[3]=SPI1->DR;

	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_1, GPIO_PIN_SET); // close spi communication adc2

	// check the value
	if(configuration[0] == 0x64 && configuration[1] == 0x94) // we have got a correct interface
	 return 0; // ok
	else
	 return 1; // id
}//end readConfiguration_ads1220_2

uint32_t read_adc1(void)
{
	uint32_t adc_data = 0;
	uint32_t return_value = 0;
	uint8_t aux = 0;
	int i;

	const int LOOP_ITERATIONS = 7;

	for (i = 0; i < LOOP_ITERATIONS; i++)
	{
		// open chip select
		HAL_GPIO_WritePin(GPIOH, GPIO_PIN_0, GPIO_PIN_RESET); // open spi communication adc1
		// START/SYNC command
		while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
		SPI1->DR=0x08;    // START/SYNC
		// fictious reading
		while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
		aux = SPI1->DR;

		// wait for data ready
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != GPIO_PIN_RESET);

		//read data ***********************************

		adc_data = 0;
		while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
		// fictious write in spi (just to start a clock and read data
		SPI1->DR=0x00;
		while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
		aux=SPI1->DR;
		adc_data |= aux;
		adc_data <<= 8;
		// fictious write in spi (just to start a clock and read data
		SPI1->DR=0x00;
		while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
		aux=SPI1->DR;
		adc_data |= aux;
		adc_data <<= 8;
		// fictious write in spi (just to start a clock and read data
		SPI1->DR=0x00;
		while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
		aux=SPI1->DR;
		adc_data |= aux;
		// close chip select
		HAL_GPIO_WritePin(GPIOH, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_SET); // close spi communication

		return_value += adc_data;
	}

	return_value /= LOOP_ITERATIONS;

	return return_value;

}// end read_adc1

uint32_t read_adc2(void)
{
	uint32_t adc_data = 0;
	uint32_t return_value = 0;
	uint8_t aux = 0;
	int i;

	const int LOOP_ITERATIONS = 77;

	// open chip select
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_1, GPIO_PIN_RESET); // open spi communication adc2
	// START/SYNC command
	while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
	SPI1->DR=0x08;    // START/SYNC
	// fictious reading
	while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
	aux = SPI1->DR;
	// close chip select
	HAL_GPIO_WritePin(GPIOH, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_SET); // close spi communication

	for (i = 0; i < LOOP_ITERATIONS; i++)
	{


		// wait for data ready
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) != GPIO_PIN_RESET);

		//read data ***********************************
		// open chip select
		HAL_GPIO_WritePin(GPIOH, GPIO_PIN_1, GPIO_PIN_RESET); // open spi communication adc2
		adc_data = 0;
		while ((SPI1->SR & SPI_FLAG_TXE) == RESET );
		// fictious write in spi (just to start a clock and read data
		SPI1->DR=0x00;
		while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
		aux=SPI1->DR;
		adc_data |= aux;
		adc_data <<= 8;
		// fictious write in spi (just to start a clock and read data
		SPI1->DR=0x00;
		while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
		aux=SPI1->DR;
		adc_data |= aux;
		adc_data <<= 8;
		// fictious write in spi (just to start a clock and read data
		SPI1->DR=0x00;
		while ((SPI1->SR & SPI_FLAG_RXNE) == RESET);
		aux=SPI1->DR;
		adc_data |= aux;
		// close chip select
		HAL_GPIO_WritePin(GPIOH, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_SET); // close spi communication

		return_value += adc_data;
	}

	return_value /= LOOP_ITERATIONS;

	return return_value;

}// end read_adc2

int *_errno(void) { return &errno; }

//***************************************************************************************************
/**
* @}
*/

/**
* @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
