/**
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warra
nty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_HAL_H
#define __USART_HAL_H

#include <stdbool.h>

/* Includes ------------------------------------------------------------------*/
#include "pinmap_hal.h"

/* Exported defines ----------------------------------------------------------*/
// Available Serial Configurations for C
#define SERIAL_8N1 (uint8_t)0b00000000
#define SERIAL_8N2 (uint8_t)0b00000001
#define SERIAL_8E1 (uint8_t)0b00000100
#define SERIAL_8E2 (uint8_t)0b00000101
#define SERIAL_8O1 (uint8_t)0b00001000
#define SERIAL_8O2 (uint8_t)0b00001001
#define SERIAL_9N1 (uint8_t)0b00010000
#define SERIAL_9N2 (uint8_t)0b00010001

// Serial Configuration masks
#define SERIAL_VALID_CONFIG (uint8_t)0b00001100
#define SERIAL_STOP_BITS (uint8_t)0b00000011
#define SERIAL_PARITY_BITS (uint8_t)0b00001100
#define SERIAL_NINE_BITS (uint8_t)0b00010000

/* Exported types ------------------------------------------------------------*/
typedef enum HAL_USART_Serial {
    HAL_USART_SERIAL1 = 0,    //maps to USART_TX_RX
    HAL_USART_SERIAL2 = 1,
    HAL_USART_SERIAL3 = 2,
    HAL_USART_SERIAL4 = 3
} HAL_USART_Serial;

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

void HAL_USART_Initial(HAL_USART_Serial serial);
void HAL_USART_Begin(HAL_USART_Serial serial, uint32_t baud);
void HAL_USART_End(HAL_USART_Serial serial);
uint32_t HAL_USART_Write_Data(HAL_USART_Serial serial, uint8_t data);
int32_t HAL_USART_Available_Data_For_Write(HAL_USART_Serial serial);
int32_t HAL_USART_Available_Data(HAL_USART_Serial serial);
int32_t HAL_USART_Read_Data(HAL_USART_Serial serial);
int32_t HAL_USART_Peek_Data(HAL_USART_Serial serial);
void HAL_USART_Flush_Data(HAL_USART_Serial serial);
bool HAL_USART_Is_Enabled(HAL_USART_Serial serial);
void HAL_USART_Half_Duplex(HAL_USART_Serial serial, bool Enable);
void HAL_USART_BeginConfig(HAL_USART_Serial serial, uint32_t baud, uint32_t config, void*);
uint32_t HAL_USART_Write_NineBitData(HAL_USART_Serial serial, uint16_t data);

#ifdef __cplusplus
}
#endif

#endif  /* __USART_HAL_H */
