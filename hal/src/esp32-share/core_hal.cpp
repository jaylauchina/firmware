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
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ui_hal.h"
#include <stdio.h>
#include "esp_system.h"
#include "nvs_flash.h"

#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"

#define EXAMPLE_WIFI_SSID  "MOLMC_NETGRAR"
#define EXAMPLE_WIFI_PASS   "26554422"

const static char *TAG = "WIFI demo";


static EventGroupHandle_t wifi_event_group;

static esp_err_t wifi_event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, 0x1);//CONNECTED_BIT);
        // openssl_client_init();
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently
           auto-reassociate. */
        esp_wifi_connect(); 
        xEventGroupClearBits(wifi_event_group, 0x1);//CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

void initVariant() __attribute__((weak));
void initVariant() {}

void init() __attribute__((weak));
void init() {}

void startWiFi() __attribute__((weak));
void startWiFi() {}

wifi_config_t wifi_config = {
    {
         EXAMPLE_WIFI_SSID,    //"MOLMC_NETGRAR",
         EXAMPLE_WIFI_PASS,//"26554422",
    },
};

void initWiFi() __attribute__((weak));
void initWiFi() {
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(wifi_event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    // printf("wifi init:%d \n",esp_wifi_init(&cfg));
    // while(1);
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    strcpy(wifi_config.sta.ssid, "MOLMC_NETGRAR");//EXAMPLE_WIFI_SSID;
    strcpy(wifi_config.sta.password, "26554422");//EXAMPLE_WIFI_SSID;
    // wifi_config_t wifi_config = {
    //     .sta = {
    //         .ssid = EXAMPLE_WIFI_SSID,    //"MOLMC_NETGRAR",
    //         .password = EXAMPLE_WIFI_PASS,//"26554422",
    //     },
    // };
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_LOGI(TAG, "start the WIFI SSID:[%s] password:[%s]\n", EXAMPLE_WIFI_SSID, EXAMPLE_WIFI_PASS);
    ESP_ERROR_CHECK( esp_wifi_start() );

}

// void setup() __attribute__((weak));
// void setup() {}
// void loop() __attribute__((weak));
// void loop() {}

// extern void loop() __attribute__((weak));
// extern void setup() __attribute__((weak));
// extern "C"{
// extern void loop();
// extern void setup();
// }
extern "C"{
void loop();
void setup();
}

// void loop() __attribute__((weak));
// void setup() __attribute__((weak));

#if 0
#include "gpio_hal.h"
#include "pinmap_hal.h"
#include "delay_hal.h"
#include "usart_hal.h"

void setup()
{
    HAL_Pin_Mode(D7, OUTPUT);
    HAL_USART_Initial(HAL_USART_SERIAL1);
    HAL_USART_Begin(HAL_USART_SERIAL1, 115200);
}

void loop()
{
    HAL_GPIO_Write(D7, 1);
    HAL_Delay_Milliseconds(1000);
    HAL_GPIO_Write(D7, 0);
    HAL_Delay_Milliseconds(1000);

    uint8_t data = 'a';
    HAL_USART_Write_Data(HAL_USART_SERIAL1, data);

}
#endif

// extern void app_loop();

void loopTask(void *pvParameters)
{
    bool setup_done = false;
    static int abc = 0;
    for(;;) {
        if(!setup_done) {
            // startWiFi();
            // HAL_UI_Initial();
            // HAL_UI_RGB_Color(RGB_COLOR_RED);
            // HAL_UI_RGB_Color(RGB_COLOR_GREEN);
            // HAL_UI_RGB_Color(RGB_COLOR_BLUE);
            setup();
            setup_done = true;
            // printf("Restarting now.\n");
        }
        loop();

        // printf("running now.\n");
    }
}

extern "C" void app_main()
{
    init();
    initVariant();

   // printf("flash stauts :%d", nvs_flash_init());

    // initWiFi();
    xTaskCreatePinnedToCore(loopTask, "loopTask", 4096, NULL, 1, NULL, 1);
}




#if 0

void HAL_Core_Setup(void);

extern "C" void system_loop_handler(uint32_t interval_us);

extern "C" void ets_update_cpu_frequency(int freqmhz);
void preloop_update_frequency() __attribute__((weak));
void preloop_update_frequency() {
#if defined(F_CPU) && (F_CPU == 160000000L)
    REG_SET_BIT(0x3ff00014, BIT(0));
    ets_update_cpu_frequency(160);
#endif
}

static uint32_t g_micros_at_task_start;
static uint32_t g_micros_at_system_loop_start;


static uint8_t intorobot_app_initial_flag = 0;
static void loop_wrapper() {
    preloop_update_frequency();
    if(!intorobot_app_initial_flag) {
        app_setup_and_loop_initial();
        intorobot_app_initial_flag = 1;
    }
    system_loop_handler(100);
    app_loop();
    run_scheduled_functions();
    esp_schedule();
}

static void loop_task(os_event_t *events) {
    g_micros_at_task_start = system_get_time();
    cont_run(&g_cont, &loop_wrapper);
    if (cont_check(&g_cont) != 0) {
       // panic();
    }
}

static void do_global_ctors(void) {
    void (**p)(void) = &__init_array_end;
    while (p != &__init_array_start)
        (*--p)();
}

extern "C" const char intorobot_subsys_version[32] __attribute__((section(".subsys.version"))) = SUBSYS_VERSION ;

void init_done() {
    gdb_init();
    do_global_ctors();
    printf("\n%08x\n", intorobot_subsys_version);
    HAL_Core_Config();
    HAL_Core_Setup();
    wlan_set_macaddr_when_init();
    esp_schedule();
}

void HAL_Core_Init(void)
{

}

void System_Loop_Handler(void* arg);
void SysTick_Handler(void* arg);
static os_timer_t systick_timer;
static os_timer_t system_loop_timer;

void HAL_Core_Config(void)
{
    //滴答定时器  //处理三色灯和模式处理
    os_timer_setfn(&systick_timer, (os_timer_func_t*)&SysTick_Handler, 0);
    os_timer_arm(&systick_timer, 1, 1);

    //Wiring pins default to inputs
    for (pin_t pin=D0; pin<=D6; pin++)
    {
        //HAL_Pin_Mode(pin, INPUT);
    }

    HAL_RTC_Initial();
    HAL_RNG_Initial();

    HAL_IWDG_Initial();
    HAL_UI_Initial();
}

void HAL_Core_Load_params(void)
{
    // load params
    HAL_PARAMS_Load_System_Params();
    HAL_PARAMS_Load_Boot_Params();
    // check if need init params
    if(INITPARAM_FLAG_FACTORY_RESET == HAL_PARAMS_Get_Boot_initparam_flag()) //初始化参数 保留密钥
    {
        DEBUG_D("init params fac\r\n");
        HAL_PARAMS_Init_Fac_System_Params();
    }
    else if(INITPARAM_FLAG_ALL_RESET == HAL_PARAMS_Get_Boot_initparam_flag()) //初始化所有参数
    {
        DEBUG_D("init params all\r\n");
        HAL_PARAMS_Init_All_System_Params();
    }
    if(INITPARAM_FLAG_NORMAL != HAL_PARAMS_Get_Boot_initparam_flag()) //初始化参数 保留密钥
    {
        HAL_PARAMS_Set_Boot_initparam_flag(INITPARAM_FLAG_NORMAL);
    }

    //保存子系统程序版本号
    char subsys_ver1[32] = {0}, subsys_ver2[32] = {0};
    HAL_Core_Get_Subsys_Version(subsys_ver1, sizeof(subsys_ver1));
    HAL_PARAMS_Get_System_subsys_ver(subsys_ver2, sizeof(subsys_ver2));
    if(strcmp(subsys_ver1, subsys_ver2))
    {
        HAL_PARAMS_Set_System_subsys_ver(subsys_ver1);
    }
}

void HAL_Core_Setup(void)
{
    esp8266_setMode(WIFI_STA);
    esp8266_setDHCP(true);
    esp8266_setAutoConnect(false);
    esp8266_setAutoReconnect(true);
    HAL_IWDG_Config(DISABLE);
    HAL_Core_Load_params();
    HAL_Bootloader_Update_If_Needed();
}

extern "C" void __real_system_restart_local();
void HAL_Core_System_Reset(void)
{
    HAL_Core_Write_Backup_Register(BKP_DR_03, 0x7DEA);
    __real_system_restart_local();
}

void HAL_Core_Enter_DFU_Mode(bool persist)
{
}

void HAL_Core_Enter_Config_Mode(void)
{
    HAL_PARAMS_Set_System_config_flag(!HAL_PARAMS_Get_System_config_flag());
    HAL_PARAMS_Save_Params();
    HAL_Core_System_Reset();
}

void HAL_Core_Enter_Firmware_Recovery_Mode(void)
{
    HAL_PARAMS_Set_Boot_boot_flag(BOOT_FLAG_DEFAULT_RESTORE);
    HAL_PARAMS_Save_Params();
    HAL_Core_System_Reset();
}

void HAL_Core_Enter_Com_Mode(void)
{
    HAL_PARAMS_Set_Boot_boot_flag(BOOT_FLAG_SERIAL_COM);
    HAL_PARAMS_Save_Params();
    HAL_Core_System_Reset();
}
/**
 * 恢复出厂设置 不清除密钥
 */

void HAL_Core_Enter_Factory_Reset_Mode(void)
{
    HAL_PARAMS_Set_Boot_boot_flag(BOOT_FLAG_FACTORY_RESET);
    HAL_PARAMS_Save_Params();
    HAL_Core_System_Reset();
}

void HAL_Core_Enter_Ota_Update_Mode(void)
{
    HAL_PARAMS_Set_Boot_boot_flag(BOOT_FLAG_OTA_UPDATE);
    HAL_PARAMS_Save_Params();
    HAL_Core_System_Reset();
}

/**
 * 恢复出厂设置 清除密钥
 */
void HAL_Core_Enter_Factory_All_Reset_Mode(void)
{
    HAL_PARAMS_Set_Boot_boot_flag(BOOT_FLAG_ALL_RESET);
    HAL_PARAMS_Save_Params();
    HAL_Core_System_Reset();
}

void HAL_Core_Enter_Safe_Mode(void* reserved)
{
}

void HAL_Core_Enter_Bootloader(bool persist)
{
}

uint16_t HAL_Core_Get_Subsys_Version(char* buffer, uint16_t len)
{
    char data[32];
    uint16_t templen;

    if (buffer!=NULL && len>0) {
        HAL_FLASH_Interminal_Read(SUBSYS_VERSION_ADDR, (uint32_t *)data, sizeof(data));
        if(!memcmp(data, "VERSION:", 8))
        {
            templen = MIN(strlen(&data[8]), len-1);
            memset(buffer, 0, len);
            memcpy(buffer, &data[8], templen);
            return templen;
        }
    }
    return 0;
}

typedef void (*app_system_loop_handler)(void);
app_system_loop_handler APP_System_Loop_Handler = NULL;

void HAL_Core_Set_System_Loop_Handler(void (*handler)(void))
{
    APP_System_Loop_Handler = handler;
}

static uint32_t g_at_system_loop = false;
void system_loop_handler(uint32_t interval_us)
{
    if( true == g_at_system_loop )
        return;

    if ((system_get_time() - g_micros_at_system_loop_start) > interval_us) {
        if (NULL != APP_System_Loop_Handler) {
            g_at_system_loop = true;
            APP_System_Loop_Handler();
            g_at_system_loop = false;
        }
        g_micros_at_system_loop_start = system_get_time();
    }
}

void SysTick_Handler(void* arg)
{
    HAL_SysTick_Handler();
    HAL_UI_SysTick_Handler();
}

void HAL_Core_System_Loop(void)
{
    optimistic_yield(100);
    system_loop_handler(100);
}

void HAL_Core_System_Yield(void)
{
    optimistic_yield(100);
}
#endif
