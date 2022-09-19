/*
 * JoyStick.h
 *
 *  Created on: Sep 15, 2022
 *      Author: hache
 */

#ifndef INC_JoyStick_H_
#define INC_JoyStick_H_

#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_adc.h"

typedef struct
{
    GPIO_TypeDef * JoyStick_xGPIO;
    GPIO_TypeDef * JoyStick_yGPIO;
    GPIO_TypeDef * JoyStick_swGPIO;
    uint16_t JoyStick_VRX_PIN;
    uint16_t JoyStick_VRY_PIN;
    uint16_t Joy_Stick_SW_PIN;
    ADC_TypeDef* ADC_Instance;
    uint32_t ADCx_CH;
    uint32_t ADCy_CH;
}JoyStick_CfgType;

void JoyStick_INIT(void);
void JoyStick_Read(uint16_t* JoyStick_XY);

#endif /* INC_JoyStick_H_ */
