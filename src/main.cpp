#include <Arduino.h>

#define BUILT_IN_RGB_LED_PIN RGB_BUILTIN

void setup()
{
  pinMode(BUILT_IN_RGB_LED_PIN, OUTPUT);
  digitalWrite(BUILT_IN_RGB_LED_PIN, LOW);

  Serial.begin(115200);
  Serial.println("Start blinky");
}

void loop()
{
  Serial.println("LED ON, Red");
  neopixelWrite(BUILT_IN_RGB_LED_PIN, RGB_BRIGHTNESS, 0, 0); // Red
  delay(1000);
  Serial.println("LED ON, Green");
  neopixelWrite(BUILT_IN_RGB_LED_PIN, 0, RGB_BRIGHTNESS, 0); // Green
  delay(1000);
  Serial.println("LED ON, Blue");
  neopixelWrite(BUILT_IN_RGB_LED_PIN, 0, 0, RGB_BRIGHTNESS); // Blue
  delay(1000);
  Serial.println("LED OFF");
  neopixelWrite(BUILT_IN_RGB_LED_PIN, 0, 0, 0); // Off / black

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  Serial.println("Hardware info");
  Serial.printf("%d cores Wifi %s%s\n", chip_info.cores, (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
                (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
  Serial.printf("Silicon revision: %d\n", chip_info.revision);
  Serial.printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
                (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embeded" : "external");

  // get chip id
  auto chipId = String((uint32_t)ESP.getEfuseMac(), HEX);
  chipId.toUpperCase();

  Serial.printf("Chip id: %s\n", chipId.c_str());

  Serial.printf("%dMB PSRAM\n", ESP.getPsramSize() / (1024 * 1024));

  delay(2000);
}
