#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"

#if CONFIG_AUTOSTART_ARDUINO

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif
#if 0
void loopTask(void *pvParameters)
{
    setup();
    for(;;) {
        loop();
    }
}

extern "C" void app_main()
{
    initArduino();
    xTaskCreatePinnedToCore(loopTask, "loopTask", 4096, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}
#endif

#endif
