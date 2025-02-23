//file: footpad.cpp
#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "driver/gpio.h"
#include "Adafruit_VL53L1X.h"

#define SDA_PIN 17
#define SCL_PIN 18
#define SHUTDOWN_PIN 45
#define IRQ_PIN 6
#define SENSOR_ADDRESS_0 0x52

Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(SHUTDOWN_PIN, IRQ_PIN);

extern "C" void app_main()
{
  initArduino();
  ESP_LOGI("APP_MAIN", "Adafruit VL53L1X sensor demo.\n");


  Wire.setPins(SDA_PIN, SCL_PIN);
  Wire.begin();
  if (! vl53.begin(SENSOR_ADDRESS_0, &Wire)) {
    ESP_LOGI("APP_MAIN", "Error on init of VL sensor: %d\n", vl53.vl_status);
    while (1)       delay(10);
  }
  ESP_LOGI("APP_MAIN", "vl53 begun. Sensor id: %#x\n", vl53.sensorID());

  if (!vl53.startRanging()) {
      ESP_LOGI("APP_MAIN", "Couldn't begin ranging, error code: %d\n", vl53.vl_status);
      while (1)     delay(10);
  }
  ESP_LOGI("APP_MAIN", "Ranging started.\n");

  vl53.setTimingBudget(50);
  ESP_LOGI("APP_MAIN", "vl53 timing budget set: %d\n", vl53.getTimingBudget());

  vl53.setROI(2, 2);

  int16_t distance;
  while(true){
      if (vl53.dataReady()){
          distance = vl53.distance();
          if (distance == -1){
              ESP_LOGI("LOOP", "Couldn't get distance.\n");
              ESP_LOGI("LOOP", "Error code: %d\n", vl53.vl_status);
          }
          ESP_LOGI("LOOP", "Distance: %dmm\n", distance);
          vl53.clearInterrupt();
      }
      distance = -1;
      vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}
