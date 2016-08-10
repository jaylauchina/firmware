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

  nfo->versionString, stringify(SYSTEM_VERSION_STRING), sizeof(info->versionString));
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/

#include "system_task.h"
#include <algorithm>
#include "system_version.h"
#include "static_assert.h"
#include "intorobot_macros.h"

using std::min;

/**
 * Series 1s (5 times), 2s (5 times), 4s (5 times), 8s (5 times) then to 16s thereafter.
 * @param connection_attempts
 * @return The number of milliseconds to backoff.
 */
unsigned backoff_period(unsigned connection_attempts)
{
    if (!connection_attempts)
        return 0;
    unsigned exponent = min(4u, (connection_attempts-1)/5);
    return 1000*(1<<exponent);
}

int system_version(char *pversion)
{
#if 0
    if(NULL != pversion)
    {
        strcpy(pversion, stringify(SYSTEM_VERSION_STRING));
        return strlen(pversion)
    }
    return SDK_ERR;
#endif
    return 0;
}
