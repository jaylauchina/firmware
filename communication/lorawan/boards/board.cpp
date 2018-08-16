/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Target board general functions implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
#include "board.h"
#include "interrupts_hal.h"
#include "delay_hal.h"
#include "wiring.h"

void DelayMs(uint32_t ms)
{
    HAL_Delay_Milliseconds(ms);
}

void BoardDisableIrq( void )
{
    HAL_disable_irq();
}

void BoardEnableIrq( void )
{
    HAL_enable_irq(0);
}

uint8_t GetBoardPowerSource( void )
{
#if 0
#if defined( USE_USB_CDC )
    if( GpioRead( &UsbDetect ) == 1 )
    {
        return BATTERY_POWER;
    }
    else
    {
        return USB_POWER;
    }
#else
    return BATTERY_POWER;
#endif
#endif
    return BATTERY_POWER;
}

