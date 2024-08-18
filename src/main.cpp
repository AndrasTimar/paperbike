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
#include <sleep.h>

RTC_DATA_ATTR int pressCount = 0;
float lastShownPercent = -2;
float lastPressCount = -1;



void displayMainScreen()
{
  float batteryLevel = checkBattery();
  if (abs(batteryLevel - lastShownPercent) > 1.0 || pressCount != lastPressCount) {
      clearScreen();
      Serial.println("Battery Level: " + String(batteryLevel) + "%");
      if (batteryLevel < 0){
        displayText("Battery Charging.", 2, 40);
      } else {
        displayText("Battery Level: " + String(batteryLevel) + "%.", 2, 40);
      }

      displayText("Press Count: " + String(pressCount), 2, 80);
      lastShownPercent = batteryLevel;
      lastPressCount = pressCount;
      updateScreen();
    }
}

void onButtonClicked()
{
  pressCount++;
  Serial.println("Button clicked");
}

void onButtonDoubleClicked()
{
  pressCount = 0;
  Serial.println("Button double clicked");
}

void onButtonLongPressed()
{
  Serial.println("Button long pressed");
  Serial.println("Going to sleep...");
  clearScreen();
  displayText("Going to sleep...", 2, 40);
  updateScreen();
  delay(1000);
  enterSleep();
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  pinMode(BATTERY_ADC_PIN, INPUT);
  analogReadResolution(12);
  // connectToWifi();
  setupButton(onButtonClicked, onButtonDoubleClicked, onButtonLongPressed);
  setupDisplay();
  Serial.println("setup done");

  // If not woken up by button press, show battery percentage
  if (!wokenByButtonPress())
  {
    Serial.println("Not woken up by button press");
    displayMainScreen();
  }
  else
  {
    Serial.println("Woken up by button press");
    // Manually call button handler, as event is not caught after deep sleep wakeup  - hacky
    onButtonClicked();
  }
  updateScreen();
}

void loop()
{
  checkButton();
  displayMainScreen();
}