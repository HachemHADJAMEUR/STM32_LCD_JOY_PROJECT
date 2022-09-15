/*
 * JOY.h
 *
 *  Created on: Sep 15, 2022
 *      Author: hache
 */

#ifndef INC_JOY_H_
#define INC_JOY_H_

#include "stm32l4xx_hal.h"

typedef struct
{
    GPIO_TypeDef * GOY_GPIO;
    uint16_t VRX_PIN;
    uint16_t VRY_PIN;
    uint16_t SW_PIN;
}JOY_CfgType;



#endif /* INC_JOY_H_ */
