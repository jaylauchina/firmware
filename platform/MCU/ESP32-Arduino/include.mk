TARGET_ESP32_SDK=$(PLATFORM_MCU_PATH)/sdk

INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/config
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/bluedroid
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/bluedroid/api
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/app_trace
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/app_update
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/bt
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/driver
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/esp32
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/esp_adc_cal
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/esp_http_client
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/esp-tls
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/ethernet
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/fatfs
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/freertos
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/heap
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/jsmn
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/log
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/mdns
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/mbedtls
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/mbedtls_port
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/newlib
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/nvs_flash
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/openssl
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/spi_flash
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/sdmmc
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/smartconfig_ack
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/spiffs
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/tcpip_adapter
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/ulp
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/vfs
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/wear_levelling
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/xtensa-debug-module
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/coap
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/console
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/expat
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/json
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/lwip
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/newlib
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/nghttp
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/soc
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/wpa_supplicant

TARGET_INTOROBOT_PATH = $(PLATFORM_MCU_PATH)/IntoRobot_Firmware_Driver
INCLUDE_DIRS += $(TARGET_INTOROBOT_PATH)/inc

ifneq ("$(MODULE)","bootloader")
INCLUDE_DIRS += $(TARGET_ESP32_SDK)/include/bootloader_support
LIB_DIRS += $(TARGET_ESP32_SDK)/lib
LIBS +=
else
LIB_DIRS +=
LIBS +=
endif

