//file: footpad.cpp
#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "driver/gpio.h"

extern "C" void app_main()
{
  ESP_LOGI("APP_MAIN", "Pre initArduino()\n");
  initArduino();
  ESP_LOGI("APP_MAIN", "Post initArduino()\n");

  /*
  // Arduino-like setup()
  Serial.begin(115200);
  while(!Serial){
    ; // wait for serial port to connect
  }
  */

  // Arduino-like loop()
  while(true){
      ESP_LOGI("APP_MAIN", "Loop.\n");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

  // WARNING: if program reaches end of function app_main() the MCU will restart.
}
