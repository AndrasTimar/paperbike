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
const int GPS_READ_INTERVAL = 5000;
const double GPS_MIN_METERS = 2.5;
unsigned long lastGPSRead = 0;
volatile double speed = 0.0;
volatile bool displayUpdating = false;

const int SCREEN_REFRESH_INTERVAL = 5000;
volatile unsigned long lastScreenUpdate = 0;
bool shouldUpdateScreen = true;
volatile float previousLat = -1;
volatile float previousLon = -1;
volatile float totalDistanceMeters = 0;

volatile float distanceResetTime = 0;

void onButtonClicked();
void onButtonDoubleClicked();
void onButtonLongPressed();
void updateDisplayTask(void *parameter);
void enterSleep();
double calculateAverageSpeedKmph();

void setup()
{
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, GPS_TX_PIN, GPS_RX_PIN);
  setupButton(onButtonClicked, onButtonDoubleClicked, onButtonLongPressed);
  screenCoordinator.switchToMainScreen();

  xTaskCreatePinnedToCore(
      updateDisplayTask,  // Task function
      "DisplayUpdate",    // Name of the task
      10000,              // Stack size (in bytes)
      NULL,               // Task input parameter
      1,                  // Priority of the task
      &DisplayTaskHandle, // Task handle
      0                   // Core where the task should run (Core 0)
  );
}

void loop()
{
  if (millis() - lastGPSRead >= GPS_READ_INTERVAL)
  {
    lastGPSRead = millis();
    while (Serial1.available())
    {
      gps.encode(Serial1.read());
    }
    if (gps.location.isUpdated())
    {
      if (previousLat != -1 && previousLon != -1)
      {
        float distance = gps.distanceBetween(previousLat, previousLon, gps.location.lat(), gps.location.lng());
        if (distance > GPS_MIN_METERS)
        {
          totalDistanceMeters += distance;
          
        }
      }
      previousLat = gps.location.lat();
      previousLon = gps.location.lng();
    }
    if (gps.speed.isUpdated())
    {
      speed = gps.speed.kmph(); // Get the speed from the GPS module
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
    screenCoordinator.updateMainScreen(checkBattery(), speed, totalDistanceMeters, calculateAverageSpeedKmph(), millis() - distanceResetTime);
    displayUpdating = false;
  }
}

void onButtonClicked()
{
  Serial.println("Button clicked");
}

void onButtonDoubleClicked()
{
  totalDistanceMeters = 0;
  distanceResetTime = millis();
  xTaskNotifyGive(DisplayTaskHandle);
}

void onButtonLongPressed()
{
  Serial.println("Button long pressed");
}

double calculateAverageSpeedKmph()
{
  unsigned long currentTime = millis();
  double averageSpeed = 0.0;

  if (totalDistanceMeters > 0 && currentTime > distanceResetTime)
  {
    unsigned long timeElapsed = currentTime - distanceResetTime; // Time elapsed in milliseconds
    // Ensure timeElapsedHours is not too small to avoid unrealistic speed values
    if (timeElapsed > 3000 && totalDistanceMeters > 0)
    {
      averageSpeed = (totalDistanceMeters / timeElapsed) * 3600; // Convert meters per millisecond to kilometers per hour
    }
  }

  return averageSpeed;
}