#define LILYGO_T5_V213

#include <Arduino.h>
#include <AceButton.h> //https://github.com/bxparks/AceButton
#include <EEPROM.h>
#define EEPROM_SIZE 10

#include <_env.h>

#include <wifi.h>
#include <display.h>

void setup() {
    Serial.begin(115200);
    Serial.println();
    Serial.println("setup");
    setupDisplay();
    connectToWifi();
    displayText("Hello World", 0, 0);
    Serial.println("setup done");
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}