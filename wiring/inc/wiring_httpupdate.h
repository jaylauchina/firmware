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

#ifndef WIRING_HTTPUPDATE_H_
#define WIRING_HTTPUPDATE_H_

#include "intorobot_config.h"

#ifndef configNO_NETWORK

#include "md5_builder.h"
#include "system_update.h"
#include "wiring_ticks.h"
#include "wiring_httpclient.h"

// note we use HTTP client errors too so we start at 100
#define HTTP_UE_TOO_LESS_SPACE              (-100)
#define HTTP_UE_SERVER_NOT_REPORT_SIZE      (-101)
#define HTTP_UE_SERVER_FILE_NOT_FOUND       (-102)
#define HTTP_UE_SERVER_FORBIDDEN            (-103)
#define HTTP_UE_SERVER_WRONG_HTTP_CODE      (-104)
#define HTTP_UE_SERVER_FAULTY_MD5           (-105)
#define HTTP_UE_BIN_VERIFY_HEADER_FAILED    (-106)
#define HTTP_UE_BIN_FOR_WRONG_FLASH         (-107)

enum HTTPUpdateResult {
    HTTP_UPDATE_FAILED,
    HTTP_UPDATE_NO_UPDATES,
    HTTP_UPDATE_OK
};

typedef HTTPUpdateResult t_httpUpdate_return; // backward compatibility

class HTTPUpdate
{
public:
    typedef void (*THandlerFunction)(void);
    typedef void (*THandlerFunction_Progress)(uint8_t);
    typedef void (*THandlerFunction_Rec)(uint8_t *data, size_t len);

    HTTPUpdate(void);
    ~HTTPUpdate(void);

    // This function is deprecated, use rebootOnUpdate and the next one instead
    t_httpUpdate_return update(const String& url, const String& currentVersion = "");
    t_httpUpdate_return update(const String& host, uint16_t port, const String& uri = "/", const String& currentVersion = "");

    size_t size();
    bool isFetching();
    size_t fetchedSize();
    bool isFetchFinish();

    int getLastError(void);
    String getLastErrorString(void);

    void setStoreStartAddress(uint32_t address);
    void setStoreMaxSize(uint32_t size);

    void onStart(THandlerFunction fn);
    void onEnd(THandlerFunction fn);
    void onProgress(THandlerFunction_Progress fn);

protected:
    t_httpUpdate_return handleUpdate(HTTPClient& http, const String& currentVersion);
    bool runUpdate(Stream& in, uint32_t size, String md5);

    uint32_t _startAddress;
    uint32_t _maxSize;
    uint32_t _size;
    uint32_t _fetchedSize;
    uint32_t _isFetching;
    uint32_t _isFetchFinish;

    THandlerFunction _start_callback;
    THandlerFunction _end_callback;
    THandlerFunction_Progress _progress_callback;

    int _lastError;
    bool _rebootOnUpdate = true;
};

#endif
#endif /* WIRING_HTTPUPDATE_H_ */

