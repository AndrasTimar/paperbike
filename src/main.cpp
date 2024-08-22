#include <TinyGPS++.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <boards.h>
#include <ui/screencoordinator.h>
#include <button.h>
#include <battery.h>

ScreenCoordinator screenCoordinator = ScreenCoordinator();
TinyGPSPlus gps;
TaskHandle_t DisplayTaskHandle = NULL;
const int GPS_READ_INTERVAL = 3000; // 5 seconds
unsigned long lastGPSRead = 0;
volatile double speed = 0.0;
volatile bool displayUpdating = false;

const int SCREEN_REFRESH_INTERVAL = 5000;
volatile unsigned long lastScreenUpdate = 0;
bool shouldUpdateScreen = true;
float previousLat = -1;
float previousLon = -1;
volatile float totalDistance = 0;

void onButtonClicked();
void onButtonDoubleClicked();
void onButtonLongPressed();
void updateDisplayTask(void *parameter);
void enterSleep();

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  setupButton(onButtonClicked, onButtonDoubleClicked, onButtonLongPressed);
  screenCoordinator.switchToMainScreen();

  xTaskCreatePinnedToCore(
      updateDisplayTask, // Task function
      "DisplayUpdate",   // Name of the task
      10000,             // Stack size (in bytes)
      NULL,              // Task input parameter
      1,                 // Priority of the task
      &DisplayTaskHandle,// Task handle
      0                  // Core where the task should run (Core 0)
  );
}

void loop()
{
  if (millis() - lastGPSRead >= GPS_READ_INTERVAL)
  {
    lastGPSRead = millis();
    if (Serial1.available())
    {
      gps.encode(Serial1.read());
    }
    if(gps.location.isUpdated()) {
      if(previousLat != -1 && previousLon != -1) {
        totalDistance += gps.distanceBetween(previousLat, previousLon, gps.location.lat(), gps.location.lng());
      }
      previousLat = gps.location.lat();
      previousLon = gps.location.lng();
    }
    if (gps.speed.isUpdated())
    {
      speed = gps.speed.kmph();                                     // Get the speed from the GPS module
    }
  }
 if (millis() - lastScreenUpdate >= SCREEN_REFRESH_INTERVAL)
  {
    lastScreenUpdate = millis();
    xTaskNotifyGive(DisplayTaskHandle);
  }
  checkButton();
}

void updateDisplayTask(void *parameter)
{
  for (;;)
  {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    displayUpdating = true;
    screenCoordinator.updateMainScreen(checkBattery(), speed, totalDistance);
    displayUpdating = false;
  }
}

void onButtonClicked()
{
  Serial.println("Button clicked");
}

void onButtonDoubleClicked()
{
  totalDistance = 0;
  xTaskNotifyGive(DisplayTaskHandle);
}

void onButtonLongPressed()
{
  Serial.println("Button long pressed");
}