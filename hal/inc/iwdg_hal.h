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

#ifndef IWDG_HAL_H
#define IWDG_HAL_H

#include <stdint.h>
#include <stdbool.h>


#ifdef	__cplusplus
extern "C" {
#endif

void HAL_IWDG_Initial(void);
void HAL_IWDG_Config(uint8_t State);
void HAL_IWDG_SetReload(uint32_t msTimeout);
void HAL_IWDG_Feed(void);


#ifdef	__cplusplus
}
#endif

#endif	/* IWDG_HAL_H */
