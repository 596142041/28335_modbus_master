/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_BOARD_H
#define __BSP_BOARD_H
  /* Includes ------------------------------------------------------------------*/
//处理器有关的头文件
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "data.h"
#include "delay.h"
#include "stdint.h"
#include "CANA.h"
#include "Flash.h"
typedef unsigned char uint8_t;
typedef char int8_t;
typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

#endif 
/********END OF FILE****/
