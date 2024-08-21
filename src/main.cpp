#define LILYGO_T5_V213

#include <Arduino.h>
#include <AceButton.h> //https://github.com/bxparks/AceButton
#include <_env.h>
#include <wifi.h>
#include <ui/screencoordinator.h>
#include <button.h>
#include <battery.h>
#include <boards.h>
#include <sleep.h>

RTC_DATA_ATTR volatile int pressCount = 0;
RTC_DATA_ATTR volatile int magnetPassedCount = 0;
int hallSensorPin = 21;  // Digital input pin

long lastRefresh = 0;
long refreshInterval = 100; 

ScreenCoordinator screenCoordinator = ScreenCoordinator();

void displayMainScreen(bool init)
{
  float batteryLevel = checkBattery();
  if(init) {
    screenCoordinator.switchToMainScreen(batteryLevel, pressCount, magnetPassedCount);
  } else {
    screenCoordinator.updateMainScreen(batteryLevel, pressCount, magnetPassedCount);
  }
}

void onMagnetPassed() {
  magnetPassedCount++;
  Serial.println("Magnet passed");
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
  screenCoordinator.switchToSleepScreen();
  enterSleep();
}

void handleInputTask(void * parameter)
{
  Serial.print("Input task running on core: ");
  Serial.println(xPortGetCoreID());
  bool magnetHight = false;
  for (;;)
  {
    int sensorValue = digitalRead(hallSensorPin);
    if (sensorValue == HIGH)
    {
      magnetHight = true;
      
    } else if (magnetHight) {
      magnetHight = false;
      onMagnetPassed();
    }
    checkButton();
    vTaskDelay(10 / portTICK_PERIOD_MS); // Slight delay to prevent task hogging the CPU
  }
}

void handleUITask(void * parameter)
{
  Serial.print("UI task running on core: ");
  Serial.println(xPortGetCoreID());
  displayMainScreen(true);
  for (;;)
  {
    if (millis() - lastRefresh > refreshInterval)
    {
      displayMainScreen(false);
      lastRefresh = millis();
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // Slight delay to prevent task hogging the CPU
  }
}
void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  pinMode(hallSensorPin, INPUT);
  pinMode(BATTERY_ADC_PIN, INPUT);
  analogReadResolution(12);
  
  setupButton(onButtonClicked, onButtonDoubleClicked, onButtonLongPressed);
  Serial.println("setup done");

  if (wokenByButtonPress())
  {
    Serial.println("Woken up by button press");
    // Manually call button handler, as event is not caught after deep sleep wakeup  - hacky
    onButtonClicked();
  }

  // Create tasks pinned to specific cores
  xTaskCreatePinnedToCore(
    handleInputTask,   // Task function
    "InputTask",       // Name of the task (for debugging)
    10000,             // Stack size (in bytes)
    NULL,              // Task input parameter
    1,                 // Priority of the task
    NULL,              // Task handle
    0                  // Core 0
  );

  xTaskCreatePinnedToCore(
    handleUITask,      // Task function
    "UITask",          // Name of the task (for debugging)
    10000,             // Stack size (in bytes)
    NULL,              // Task input parameter
    1,                 // Priority of the task
    NULL,              // Core 1
    1                  // Core 1
  );
}

void loop()
{}