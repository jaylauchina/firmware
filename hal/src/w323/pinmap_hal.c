/**
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "pinmap_hal.h"
#include "pinmap_impl.h"
#include <stddef.h>

#define NONE CHANNEL_NONE

#define GPIO0                      0     // GPIO_NUM_0
#define GPIO1                      1     // GPIO_NUM_1
#define GPIO2                      2     // GPIO_NUM_2
#define GPIO3                      3     // GPIO_NUM_3
#define GPIO4                      4     // GPIO_NUM_4
#define GPIO5                      5     // GPIO_NUM_5
#define GPIO6                      6     // GPIO_NUM_6
#define GPIO7                      7     // GPIO_NUM_7
#define GPIO8                      8     // GPIO_NUM_8
#define GPIO9                      9     // GPIO_NUM_9
#define GPIO10                     10
#define GPIO11                     11
#define GPIO12                     12
#define GPIO13                     13
#define GPIO14                     14
#define GPIO15                     15
#define GPIO16                     16
#define GPIO17                     17
#define GPIO18                     18
#define GPIO19                     19
#define GPIO20                     20
#define GPIO21                     21
#define GPIO22                     22
#define GPIO23                     23
#define GPIO24                     24
#define GPIO25                     25
#define GPIO26                     26
#define GPIO27                     27
#define GPIO28                     28
#define GPIO29                     29
#define GPIO30                     30
#define GPIO31                     31
#define GPIO32                     32
#define GPIO33                     33
#define GPIO34                     34 /* input mode only */
#define GPIO35                     35 /* input mode only */
#define GPIO36                     36 /* input mode only */
#define GPIO37                     37 /* input mode only */
#define GPIO38                     38 /* input mode only */
#define GPIO39                     39 /* input mode only */


#define ADC_CHANNEL  ((uint8_t)0x01)
#define DAC_CHANNEL  ((uint8_t)0x01)

#define ESP32_TIMER_0  0
#define ESP32_TIMER_1  1
#define ESP32_TIMER_2  2
#define ESP32_TIMER_3  3

#define TIMER_PWM_CHANNEL_0 0
#define TIMER_PWM_CHANNEL_1 1
#define TIMER_PWM_CHANNEL_2 2
#define TIMER_PWM_CHANNEL_3 3
#define TIMER_PWM_CHANNEL_4 4
#define TIMER_PWM_CHANNEL_5 5
#define TIMER_PWM_CHANNEL_6 6
#define TIMER_PWM_CHANNEL_7 7
#define TIMER_PWM_CHANNEL_8 8
#define TIMER_PWM_CHANNEL_9 9
#define TIMER_PWM_CHANNEL_10 10
#define TIMER_PWM_CHANNEL_11 11
#define TIMER_PWM_CHANNEL_12 12
#define TIMER_PWM_CHANNEL_13 13
#define TIMER_PWM_CHANNEL_14 14
#define TIMER_PWM_CHANNEL_15 15

/* Private typedef -----------------------------------------------------------*/

ESP32_Pin_Info __PIN_MAP[TOTAL_PINS] =
{
/*
 * gpio_pin (0-16)
 * gpio_pin_source (GPIO_PinSource0 - GPIO_PinSource15)
 * adc_channel
 * dac_channel
 * timer_peripheral (TIM1 - TIM5, or NONE)
 * timer_ch (1-3, or NONE)
 * pin_mode (NONE by default, can be set to OUTPUT, INPUT, or other types)
 */
/*             - 00 */ { GPIO1, NONE, NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/*             - 01 */ { GPIO3, NONE, NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/*             - 02 */ { GPIO5, NONE, NONE, NONE, ESP32_TIMER_0, TIMER_PWM_CHANNEL_0, PIN_MODE_NONE, 0 },
/*             - 03 */ { GPIO16, NONE, NONE, NONE, ESP32_TIMER_0, TIMER_PWM_CHANNEL_1, PIN_MODE_NONE, 0 },
/*             - 04 */ { GPIO17, NONE, NONE, NONE, ESP32_TIMER_1, TIMER_PWM_CHANNEL_2, PIN_MODE_NONE, 0 },
/*             - 05 */ { GPIO18, NONE, NONE, NONE, ESP32_TIMER_1, TIMER_PWM_CHANNEL_3, PIN_MODE_NONE, 0 },
/*             - 06 */ { GPIO19, NONE, NONE, NONE, ESP32_TIMER_2, TIMER_PWM_CHANNEL_4, PIN_MODE_NONE, 0 },
/*             - 07 */ { GPIO21, NONE, NONE, NONE, ESP32_TIMER_2, TIMER_PWM_CHANNEL_5, PIN_MODE_NONE, 0 },
/*             - 08 */ { GPIO22, NONE, NONE, NONE, ESP32_TIMER_3, TIMER_PWM_CHANNEL_6, PIN_MODE_NONE, 0 },
/*             - 09 */ { GPIO23, NONE, NONE, NONE, ESP32_TIMER_3, TIMER_PWM_CHANNEL_7, PIN_MODE_NONE, 0 },
/* NOT USED    - 10 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 11 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 12 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 13 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 14 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 15 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 16 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 17 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 18 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 19 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 20 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 21 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 22 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 23 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 24 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 25 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 26 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 27 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 28 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/* NOT USED    - 29 */ { NONE, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/*             - 30 */ { GPIO0,  NONE, ADC_CHANNEL, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/*             - 31 */ { GPIO2,  NONE, ADC_CHANNEL, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/*             - 32 */ { GPIO4,  NONE, ADC_CHANNEL, NONE, ESP32_TIMER_0, TIMER_PWM_CHANNEL_8, PIN_MODE_NONE, 0 },
/*             - 33 */ { GPIO12, NONE, ADC_CHANNEL, NONE, ESP32_TIMER_0, TIMER_PWM_CHANNEL_9, PIN_MODE_NONE, 0 },
/*             - 34 */ { GPIO13, NONE, ADC_CHANNEL, NONE, ESP32_TIMER_1, TIMER_PWM_CHANNEL_10, PIN_MODE_NONE, 0 },
/*             - 35 */ { GPIO14, NONE, ADC_CHANNEL, NONE, ESP32_TIMER_1, TIMER_PWM_CHANNEL_11, PIN_MODE_NONE, 0 },
/*             - 36 */ { GPIO15, NONE, ADC_CHANNEL, NONE, ESP32_TIMER_2, TIMER_PWM_CHANNEL_12, PIN_MODE_NONE, 0 },
/*             - 37 */ { GPIO25, NONE, ADC_CHANNEL, DAC_CHANNEL, ESP32_TIMER_2, TIMER_PWM_CHANNEL_13, PIN_MODE_NONE, 0 },
/*             - 38 */ { GPIO26, NONE, ADC_CHANNEL, DAC_CHANNEL, ESP32_TIMER_3, TIMER_PWM_CHANNEL_14, PIN_MODE_NONE, 0 },
/*             - 39 */ { GPIO27, NONE, ADC_CHANNEL, NONE, ESP32_TIMER_3, TIMER_PWM_CHANNEL_15, PIN_MODE_NONE, 0 },
/*             - 40 */ { GPIO32, NONE, ADC_CHANNEL, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/*             - 41 */ { GPIO33, NONE, ADC_CHANNEL, NONE, NONE, NONE, PIN_MODE_NONE, 0 },
/*             - 42 */ { GPIO34, NONE, ADC_CHANNEL, NONE, PIN_MODE_NONE, 0 },
/*             - 43 */ { GPIO35, NONE, ADC_CHANNEL, NONE, PIN_MODE_NONE, 0 },
/*             - 44 */ { GPIO36, NONE, ADC_CHANNEL, NONE, PIN_MODE_NONE, 0 },
/*             - 45 */ { GPIO39, NONE, ADC_CHANNEL, NONE, PIN_MODE_NONE, 0 },
};

ESP32_Pin_Info* HAL_Pin_Map() {
    return __PIN_MAP;
}

