#include <Arduino.h>
#include <boards.h>

// 18650 li-ion battery
const float maxVoltage = 4.2; // maximum voltage for your battery
const float minVoltage = 3.0; // minimum voltage for your battery

//-1.0 means charging, assuming the circuit is charging when voltage is above 4.3V
float checkBattery()
{
    float voltage = analogRead(BATTERY_ADC_PIN) / 4096.0 * 7.46;
    uint8_t percentage = 0;
    Serial.println("Voltage = " + String(voltage));
    if(voltage > 4.3) {
        return -1.0; // signal charging
    }
    if (voltage > 1)
    { // Only display if there is a valid reading
        percentage = 2836.9625 * pow(voltage, 4) - 43987.4889 * pow(voltage, 3) + 255233.8134 * pow(voltage, 2) - 656689.7123 * voltage + 632041.7303;
        if (voltage >= 4.20)
            percentage = 100;
        if (voltage <= 3.50)
            percentage = 0;
        Serial.println("Percentage = " + String(percentage));
    }
    return percentage;
}