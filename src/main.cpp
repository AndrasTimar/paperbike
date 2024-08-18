#define LILYGO_T5_V213

#include <Arduino.h>
#include <AceButton.h> //https://github.com/bxparks/AceButton
#include <EEPROM.h>
#define EEPROM_SIZE 10

#include <_env.h>

#include <wifi.h>
#include <ui/screencoordinator.h>
#include <button.h>
#include <battery.h>
#include <boards.h>
#include <sleep.h>

RTC_DATA_ATTR int pressCount = 0;

long lastRefresh = 0;
long refreshInterval = 500;

ScreenCoordinator screenCoordinator = ScreenCoordinator();

void displayMainScreen()
{
  float batteryLevel = checkBattery();
  screenCoordinator.showMainScreen(batteryLevel, pressCount);
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
  screenCoordinator.showSleepScreen();
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
  Serial.println("setup done");

  // If not woken up by button press, show battery percentage
  if (!wokenByButtonPress())
  {
    Serial.println("Not woken up by button press");
  }
  else
  {
    Serial.println("Woken up by button press");
    // Manually call button handler, as event is not caught after deep sleep wakeup  - hacky
    onButtonClicked();
  }
  displayMainScreen();
}

void loop()
{
  checkButton();
  if (millis() - lastRefresh > refreshInterval)
  {
    switch(screenCoordinator.screenType){
    case MAIN:
      displayMainScreen();
      break;
    case SLEEP:
      screenCoordinator.showSleepScreen();
      break;
  }

    lastRefresh = millis();
  }
  
}