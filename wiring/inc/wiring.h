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

#ifndef WIRING_H_
#define WIRING_H_

#include "pinmap_hal.h"
#include "gpio_hal.h"
#include "adc_hal.h"
#include "dac_hal.h"
#include "pwm_hal.h"
#include "rng_hal.h"
#include "config.h"
#include "intorobot_macros.h"
#include "service_debug.h"
#include "wiring_arduino.h"
#include "wiring_constants.h"
#include "wiring_stream.h"
#include "wiring_printable.h"
#include "wiring_ipaddress.h"
#include "wiring_cellular_printable.h"
#include "wiring_wifi.h"
#include "wiring_cellular.h"
#include "wiring_character.h"
#include "wiring_random.h"
#include "wiring_system.h"
#include "wiring_cloud.h"
#include "wiring_rgb.h"
#include "wiring_ticks.h"

/* To prevent build error, we are undefining and redefining DAC here */
#undef DAC
#define DAC DAC1

#ifdef __cplusplus
extern "C" {
#endif

/*
* ADC
*/
void setADCSampleTime(uint8_t ADC_SampleTime);
int32_t analogRead(pin_t pin);

/*
* GPIO
*/
void pinMode(pin_t pin, PinMode mode);
PinMode getPinMode(pin_t pin);
bool pinAvailable(pin_t pin);
void digitalWrite(pin_t pin, uint8_t value);
int32_t digitalRead(pin_t pin);


long map(long value, long fromStart, long fromEnd, long toStart, long toEnd);

void shiftOut(pin_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(pin_t dataPin, uint8_t clockPin, uint8_t bitOrder);

void serialReadLine(Stream *serialObj, char *dst, int max_len, system_tick_t timeout);

uint32_t timerGetId(void);
bool timerIsEnd(uint32_t timerID, uint32_t time);

#ifdef __cplusplus
}
#endif

uint32_t pulseIn(pin_t pin, uint16_t value, uint32_t timeout = 1000000L);
uint32_t pulseInLong(pin_t pin, uint16_t value, uint32_t timeout = 1000000L);
void analogWrite(pin_t pin, uint32_t value);
void analogWrite(pin_t pin, uint32_t value, uint32_t pwm_frequency);
uint8_t analogWriteResolution(pin_t pin, uint8_t resolution);
uint8_t analogWriteResolution(pin_t pin);
uint32_t analogWriteMaxFrequency(pin_t pin);
void setDACBufferred(pin_t pin, uint8_t state);

#endif /* __WIRING_H_ */
