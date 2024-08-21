#pragma once

#include <Arduino.h>
#include <vector>

const int HALL_PIN = 21;  // Digital input pin
class HallSensorSpeedService {
public:
    HallSensorSpeedService() 
      : passCount(0), currentHallSensorValue(false), wheelCircumferenceInCm(210) {}

    void init() {
        pinMode(HALL_PIN, INPUT);
    }

    void checkSensor() {
        int hallValue = digitalRead(HALL_PIN);
        if (hallValue == HIGH && !currentHallSensorValue) {  // Detect rising edge
            currentHallSensorValue = true;
            passCount++;
            Serial.println("Pass detected, count: " + String(passCount));
            passTimes.push_back(millis());
        } else if (hallValue == LOW) {
            currentHallSensorValue = false;
        }
    }

    // Get the last passTimes in the interval before now() and calculate the average speed
    float getSpeedInKmH(int intervalSeconds) {
        Serial.println("Calculating speed: " + String(millis()));
        unsigned long now = millis();
        unsigned long interval = intervalSeconds * 1000;
        unsigned long intervalStart = now - interval;
        int passCountInInterval = 0;
        unsigned long lastPassTime = 0;

        // Iterate from the end of passTimes backwards
        for (int i = passTimes.size() - 1; i >= 0; i--) {
            if (passTimes[i] < intervalStart) {
                break;  // Exit loop if we're outside the interval
            }
            passCountInInterval++;
            lastPassTime = passTimes[i];
            Serial.println("Counted pass at index " + String(i) + ", total count: " + String(passCountInInterval));
        }

        if (passCountInInterval == 0) {
            Serial.println("No passes in interval");
            return 0;
        }

        // Ensure lastPassTime is valid
        if (lastPassTime == 0) {
            Serial.println("Invalid lastPassTime");
            return 0;
        }

        float distanceInMKm = passCountInInterval * wheelCircumferenceInCm / 100000.0;

        // Calculate speed in km/h
        float kmph = distanceInMKm / ((now - intervalStart) / 1000.0 / 3600.0);
        Serial.println("Speed: " + String(kmph) + " km/h");
        float passesPerSecond = passCountInInterval / (interval / 1000.0);
        Serial.println("Passes per second: " + String(passesPerSecond));

        return kmph;
    }

private:
    volatile int passCount;
    std::vector<unsigned long> passTimes;
    bool currentHallSensorValue;
    int wheelCircumferenceInCm;
};
