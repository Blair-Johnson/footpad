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
  ESP_LOGI("APP_MAIN", "Pre initArduino()\n");
  initArduino();
  ESP_LOGI("APP_MAIN", "Post initArduino()\n");

  // Arduino-like setup()
  Serial.begin(115200);
  while(!Serial){
    ; // wait for serial port to connect
  }
  ESP_LOGI("APP_MAIN", "Serial connected.\n");
  ESP_LOGI("APP_MAIN", "Adafruit VL53L1X sensor demo.\n");


  Wire.setPins(SDA_PIN, SCL_PIN);
  Wire.begin();
  if (! vl53.begin(SENSOR_ADDRESS_0, &Wire)) {
    ESP_LOGI("WIRE", "Error on init of VL sensor: %d\n", vl53.vl_status);
    while (1)       delay(10);
  }
  ESP_LOGI("WIRE", "vl53 begun.\n");

  vl53.setTimingBudget(50);
  ESP_LOGI("APP_MAIN", "vl53 timing budget set: %d\n", vl53.getTimingBudget());


  // Arduino-like loop()
  while(true){
      int16_t distance;

      if (vl53.dataReady()){
          distance = vl53.distance();
          if (distance != -1){
              ESP_LOGI("LOOP", "Couldn't get distance.\n");
              ESP_LOGI("LOOP", "Error code: %d\n", vl53.vl_status);
          }
          ESP_LOGI("LOOP", "Distance: %dmm\n", distance);
          vl53.clearInterrupt();
      }
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

  // WARNING: if program reaches end of function app_main() the MCU will restart.
}
