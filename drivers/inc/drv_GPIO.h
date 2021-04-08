
/**
  ******************************************************************************
  * @Company    : Name of company
  * @file       : name_of_file.h
  * @author     : Name of author
  * @version	  : version of driver, API or application files 
  * @date       : Data of the file was created
  * @brief      : What this file does
  ******************************************************************************
*/ 
#if 1 
// #ifdef GPIO_ENABLED

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __file_name_drv_gpio_H
#define __file_name_drv_gpio_H

/* Includes ------------------------------------------------------------------*/
// STM32
#include "stm32f1xx_hal.h"
/* Define --------------------------------------------------------------------*/
#define NUM_OF_IOS  2U

/* DEFINING PORT AND PINS FOR THE DIGITAL I/Os USED --------------------------*/
/* OUTPUTS -------------------------------------------------------------------*/
#define LED_Pin     GPIO_PIN_5
#define LED_Port    GPIOA
/*----------------------------------------------------------------------------*/
/* INPUTS --------------------------------------------------------------------*/
#define PushButton_Pin GPIO_PIN_13
#define PushButton_Port GPIOC
#define PushButton_EXTI_IRQn EXTI15_10_IRQn
/*----------------------------------------------------------------------------*/

/* Typedef -------------------------------------------------------------------*/
// These values helps to understand the code
typedef enum
{                       
    /* Output *****************************************************************/
    eLED,
    /* Input ******************************************************************/
    ePushButton
} e_gpio_t;

// This struct combines port and pin in one location
typedef struct
{
    GPIO_TypeDef    *port;
    uint16_t        pin;        
    
} st_gpio_pin_t;

// Struct that retains all information about GPIOs of application
typedef struct
{
    /* Flags ******************************************************************/
    bool bFlagEnable;	        		// State of peripheral
    
    /* Variables **************************************************************/
	GPIO_PinState bState[NUM_OF_IOS];	// Vector of GPIOs values stored
    
    /* Function Pointers ******************************************************/
    int8_t  (*Open) (void);                        
    int8_t  (*Close)(void);                    
    int8_t  (*Write)(e_gpio_t, GPIO_PinState);              
    int8_t  (*Read) (e_gpio_t);               
    
} st_gpio_t;

/* Public objects ------------------------------------------------------------*/
extern st_gpio_t GPIO;

#endif /* __file_name_drv_gpio_H */
#endif /* GPIO_ENABLED */

/*****************************END OF FILE**************************************/