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
#ifndef UPDATER_HAL_H
#define UPDATER_HAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum {
    UPDATER_MODE_UPDATE,
    UPDATER_MODE_DOWNLOAD
} updater_mode_t;

typedef void (*THandlerFunction_Progress)(uint8_t *data, size_t len, uint32_t currentSize, uint32_t totalSize);

bool HAL_Update(const char *host, const char *uri, const char * md5, updater_mode_t mode);
void HAL_Set_Update_Handle(THandlerFunction_Progress fn);
void HAL_Set_Update_Flag(uint32_t size);
uint32_t HAL_Update_StartAddress();
uint32_t HAL_Update_FlashLength();
int HAL_Update_Flash(const uint8_t *pBuffer, uint32_t address, uint32_t length, void* reserved);


#ifdef __cplusplus
}
#endif

#endif /* UPDATER_HAL_H */
