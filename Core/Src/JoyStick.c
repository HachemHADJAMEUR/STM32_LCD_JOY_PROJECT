/*
 * JoyStick.c
 *
 *  Created on: Sep 15, 2022
 *      Author: hache
 */

#include "JoyStick.h"
#include "JoyStick_cfg.h"
#include "DWT_Delay.h"
#include "errno.h"

static ADC_HandleTypeDef hadc;
static ADC_ChannelConfTypeDef sConfig = {0};
static void MX_ADC_Init(ADC_TypeDef * ADC_Instance, uint32_t ADC_Channel)
{

  ADC_ChannelConfTypeDef sConfig = {0};

  /** Common config
  */
  hadc.Instance = ADC_Instance;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV12;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.NbrOfConversion = 1;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_Channel;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_SINGLE_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

void JoyStick_INIT(){
  GPIO_InitTypeDef GPIO_InitStruct ={0};

  if(JoyStick_CfgParam.JoyStick_xGPIO == GPIOA || JoyStick_CfgParam.JoyStick_yGPIO == GPIOA || JoyStick_CfgParam.JoyStick_swGPIO == GPIOA)
        __HAL_RCC_GPIOA_CLK_ENABLE();
  if(JoyStick_CfgParam.JoyStick_xGPIO == GPIOB || JoyStick_CfgParam.JoyStick_yGPIO == GPIOB || JoyStick_CfgParam.JoyStick_swGPIO == GPIOB)
        __HAL_RCC_GPIOB_CLK_ENABLE();
  if(JoyStick_CfgParam.JoyStick_xGPIO == GPIOC || JoyStick_CfgParam.JoyStick_yGPIO == GPIOC || JoyStick_CfgParam.JoyStick_swGPIO == GPIOC)
      __HAL_RCC_GPIOC_CLK_ENABLE();
  if (JoyStick_CfgParam.JoyStick_xGPIO == GPIOD || JoyStick_CfgParam.JoyStick_yGPIO == GPIOD || JoyStick_CfgParam.JoyStick_swGPIO == GPIOD)
      __HAL_RCC_GPIOD_CLK_ENABLE();

  GPIO_InitStruct.Pin = JoyStick_CfgParam.JoyStick_VRX_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  HAL_GPIO_Init(JoyStick_CfgParam.JoyStick_xGPIO, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = JoyStick_CfgParam.JoyStick_VRY_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(JoyStick_CfgParam.JoyStick_yGPIO, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = JoyStick_CfgParam.Joy_Stick_SW_PIN;
      GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
      HAL_GPIO_Init(JoyStick_CfgParam.JoyStick_swGPIO, &GPIO_InitStruct);

      MX_ADC_Init(JoyStick_CfgParam.ADC_Instance, JoyStick_CfgParam.ADCx_CH);

}

void JoyStick_Read(uint16_t* JoyStick_XY)
{
  uint16_t AD_RES;
    sConfig.Channel = JoyStick_CfgParam.ADCx_CH;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
    {
      Error_Handler();
    }
    HAL_GPIO_WritePin(JoyStick_CfgParam.JoyStick_xGPIO, JoyStick_CfgParam.JoyStick_VRX_PIN, GPIO_PIN_SET);
    HAL_ADC_ConfigChannel(&hadc, &sConfig);
    HAL_ADC_Start(&hadc);
    HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
    AD_RES = HAL_ADC_GetValue(&hadc);
    HAL_GPIO_WritePin(JoyStick_CfgParam.JoyStick_xGPIO, JoyStick_CfgParam.JoyStick_VRX_PIN, GPIO_PIN_RESET);
    JoyStick_XY[0] = AD_RES;

    sConfig.Channel = JoyStick_CfgParam.ADCy_CH;
        if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
        {
          Error_Handler();
        }
        HAL_GPIO_WritePin(JoyStick_CfgParam.JoyStick_yGPIO, JoyStick_CfgParam.JoyStick_VRY_PIN, GPIO_PIN_SET);
        HAL_ADC_ConfigChannel(&hadc, &sConfig);
        HAL_ADC_Start(&hadc);
        HAL_ADC_PollForConversion(&hadc, HAL_MAX_DELAY);
        AD_RES = HAL_ADC_GetValue(&hadc);
        HAL_GPIO_WritePin(JoyStick_CfgParam.JoyStick_yGPIO, JoyStick_CfgParam.JoyStick_VRY_PIN, GPIO_PIN_RESET);
        JoyStick_XY[1] = AD_RES;
}


