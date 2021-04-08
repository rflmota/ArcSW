
/**
  ******************************************************************************
  * @Company    : Name of company
  * @file       : name_of_file.c
  * @author     : Name of author
  * @version	: version of driver, API or application files 
  * @date       : Data of the file was created
  * @brief      : What this file does
  ******************************************************************************
*/ 
#if 1
// #ifdef GPIO_ENABLED

/* Includes ------------------------------------------------------------------*/ 
// C language standard library
#include <stdint.h>
// Eder Andrade driver library
#include "drv_GPIO.h"
// Application

/*******************************************************************************
							               HOW TO USE THIS DRIVER
********************************************************************************

1. 	First, you should include in your .c file: "company_name_drv_gpio.h" and call GPIO object,
	after that, you can use the follow resources of the driver

	- GPIO: this is the object that will control the peripheral;	

	Data -----------------------------------------------------------------------

	- GPIO.bFlagEnable	===================> It informs if GPIO driver is enabled
	- GPIO.bState[x]	===================> Stores the state of a specific pin

	Methods --------------------------------------------------------------------

	- GPIO.Open() =========================> Initializes the GPIO driver;
	- GPIO.Close() ========================> Finishes the GPIO driver;
	- GPIO.Write() ========================> Writes "0" or "1" on a specific pin
	- GPIO.Read() =========================> Read the state of a specific pin

*******************************************************************************/

/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const static st_gpio_pin_t IO[NUM_OF_IOS] = 
{
	{LED_Port,        LED_Pin       },
  {PushButton_Port, PushButton_Pin}	

};

/* Private function prototypes -----------------------------------------------*/    
static int8_t   gpio_open   (void);					// Initialize the peripheral
static int8_t   gpio_close  (void);                    // Close the peripheral
static int8_t   gpio_write  (e_gpio_t, GPIO_PinState);  	// Write (0 or 1) on a specific pin
static int8_t   gpio_read   (e_gpio_t);             	// Read state of a specific pin

/* Public objects ------------------------------------------------------------*/
st_gpio_t GPIO = 
{
    /* Peripheral disabled ****************************************************/
    .bFlagEnable			= RESET,
    
    /* All pins are reseted ***************************************************/
    .bState[NUM_OF_IOS]= {RESET}, 
    
    /* Function pointers loaded ***********************************************/
    .Open   				= &gpio_open	,
    .Close  				= &gpio_close	,
    .Write  				= &gpio_write	,
    .Read   				= &gpio_read
    
};

/* Body of private functions -------------------------------------------------*/

/**
 * @brief  EXTI line detection callbacks.
 * @param  GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	/* Prevent unused argument(s) compilation warning */
	UNUSED(GPIO_Pin);
}

/**
  * @Func       : name of function    
  * @brief      : Put your description here
  * @pre-cond.  : Conditions needed to APIs/drivers work
  * @post-cond. : Conditions achieved after API/drivers executed
  * @parameters : Fill this field wherever there is or not parameter / returning
  * @retval     : Fill this field wherever there is or not parameter / returning
  */
static int8_t gpio_open(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PC0 PC1 PC2 PC3
							 PC4 PC5 PC6 PC7
							 PC8 PC9 PC10 PC11
							 PC12 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 |
						  GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |
						  GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PA1 PA2 PA3 PA4
							 PA6 PA7 PA8 PA11
							 PA12 PA15 */
	GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_6 |
						  GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : LD2_Pin */
	GPIO_InitStruct.Pin = LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PB0 PB1 PB2 PB10
							 PB11 PB12 PB13 PB14
							 PB15 PB4 PB5 PB6
							 PB7 PB8 PB9 */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_10 | GPIO_PIN_11 |
						  GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_4 |
						  GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : PD2 */
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* EXTI interrupt init*/
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	GPIO.bFlagEnable = SET;	
	// GPIO enabled!
	return 0;	
}

/**
  * @Func       : name of function    
  * @brief      : Put your description here
  * @pre-cond.  : Conditions needed to APIs/drivers work
  * @post-cond. : Conditions achieved after API/drivers executed
  * @parameters : Fill this field wherever there is or not parameter / returning
  * @retval     : Fill this field wherever there is or not parameter / returning
  */
static int8_t company_name_gpio_close(void)
{
	// Check if GPIO was enabled
    if(GPIO.bFlagEnable != RESET)
    {        
        // Clean up the pin state vector
        for(uint8_t i = 0; i < NUM_OF_IOS; i++)
        {
            // Reset the values
            GPIO.bState[i] = RESET;
        }        
		
		// Clear all ports
    for (size_t idx = 0; i < idx; idx++)
		  HAL_GPIO_DeInit(IO[idx].port, IO[idx].pin);
    
		// IOs disable
		GPIO.bFlagEnable = RESET;

		// OK
		return 0;
    }
	// GPIO is disabled
	return -1;
}

/**
  * @Func       : name of function    
  * @brief      : Put your description here
  * @pre-cond.  : Conditions needed to APIs/drivers work
  * @post-cond. : Conditions achieved after API/drivers executed
  * @parameters : Fill this field wherever there is or not parameter / returning
  * @retval     : Fill this field wherever there is or not parameter / returning
  */
static int8_t company_name_gpio_write(e_gpio_t eHw, BitStatus bValue)
{    
    // Check if GPIO is enabled
    if(GPIO.bFlagEnable != RESET)
    {        
		// Verifies which action is gonna happens
		if(bValue == SET)
		{
			// Set pin
		}
		else if(bValue == RESET)
		{
			// Reset pin
		}        
		else
		{
			// Some other value different of "0" or "1" was passed 
			return -1;
		}
		// Update the state of pin chosen
        GPIO.bState[eHw] = bValue;				
		// OK
		return 0;		
    }
	// GPIO is disabled
    return -2;
}

/**
  * @Func       : name of function    
  * @brief      : Put your description here
  * @pre-cond.  : Conditions needed to APIs/drivers work
  * @post-cond. : Conditions achieved after API/drivers executed
  * @parameters : Fill this field wherever there is or not parameter / returning
  * @retval     : Fill this field wherever there is or not parameter / returning
  */
static int8_t company_name_gpio_read(e_gpio_t eHw)
{        
    // Check if GPIO was enabled
    if(GPIO.bFlagEnable != RESET)
    {
        // Load the buffer with value of pin specified
		
	    // retun the state
    	return GPIO.bState[eHw];
    }
	// GPIO is disabled
    return -1;
}
#endif /* GPIO_ENABLED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*****************************END OF FILE**************************************/