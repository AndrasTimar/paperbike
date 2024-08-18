#define LILYGO_T5_V213

#include <Arduino.h>
#include <AceButton.h> //https://github.com/bxparks/AceButton
#include <EEPROM.h>
#define EEPROM_SIZE 10

#include <_env.h>

#include <wifi.h>
#include <display.h>
#include <button.h>
#include <battery.h>
#include <boards.h>

RTC_DATA_ATTR int pressCount = 0;

void button1Clicked() {
  pressCount++;
  clearScreen(false);
  
  float batteryLevel = checkBattery();
  
  displayText("Battery Level: " + String(batteryLevel) + "%");

  Serial.println("Button 1 clicked@@@@@@@@@@ ");
}

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("setup");
    setupDisplay();
    //connectToWifi();
    displayText("Hello World");
    setupButton(button1Clicked);
    Serial.println("setup done");
    pinMode(BATTERY_ADC_PIN, INPUT);
    analogReadResolution(12);
}

void loop() {
   checkButton();
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}