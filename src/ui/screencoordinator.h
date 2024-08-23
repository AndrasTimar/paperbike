#pragma once

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <boards.h>
#include <Arduino.h>
#include <ui/screencoordinator.h>
#include <ui/mainscreen.h>
#include <ui/sleepscreen.h>
#include <ui/debugscreen.h>
#include <mutex>

enum ScreenType
{
    SLEEP,
    MAIN,
    DEBUG
};

class ScreenCoordinator
{
private:
    MainScreen *mainScreen = nullptr;
    SleepScreen *sleepScreen = nullptr;
#if DEBUG_MODE
    DebugScreen *debugScreen = nullptr;
#endif
    GxIO_Class io;
    GxEPD_Class *display;
    std::mutex screenMutex;

    // Delete the copy constructor and copy assignment operator
    ScreenCoordinator(const ScreenCoordinator&) = delete;
    ScreenCoordinator& operator=(const ScreenCoordinator&) = delete;

    // Optional: Implement the move constructor and move assignment operator
    ScreenCoordinator(ScreenCoordinator&& other) noexcept = default;
    ScreenCoordinator& operator=(ScreenCoordinator&& other) noexcept = default;

public:
    volatile ScreenType screenType;

    ScreenCoordinator() : io(SPI, EPD_CS, EPD_DC, EPD_RSET)
    {
        SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);
        display = new GxEPD_Class(io, EPD_RSET, EPD_BUSY);
        display->init();
        display->setTextSize(2);
        display->setRotation(1);
        mainScreen = new MainScreen(display);
        sleepScreen = new SleepScreen(display);
#if DEBUG_MODE
        debugScreen = new DebugScreen(display);
#endif
        display->fillScreen(GxEPD_WHITE);
        display->update();
    };

    void switchToMainScreen()
    {
        std::lock_guard<std::mutex> lock(screenMutex);
        screenType = MAIN;
        display->fillScreen(GxEPD_WHITE);
        display->update();
        mainScreen->init();
    }

    void updateMainScreen(float batteryLevel, double speedKmph, double totalDistance, double averageSpeed, double legTimeMs)
    {
        std::lock_guard<std::mutex> lock(screenMutex);
        if (screenType == MAIN)
        {
            mainScreen->update(batteryLevel, speedKmph, totalDistance, averageSpeed, legTimeMs);
        }
    }

    void switchToSleepScreen()
    {
        std::lock_guard<std::mutex> lock(screenMutex);
        screenType = SLEEP;
        display->fillScreen(GxEPD_WHITE);
        display->update();
        sleepScreen->init();
    };

    void switchToDebugScreen()
    {
#if DEBUG_MODE
        std::lock_guard<std::mutex> lock(screenMutex);
        screenType = DEBUG;
        display->fillScreen(GxEPD_WHITE);
        display->update();
        debugScreen->init();
#endif
    }

    void updateDebugScreen(float totalUnfilteredDistance, int unfilteredUpdateCount, int actualUpdateCount)
    {
        std::lock_guard<std::mutex> lock(screenMutex);
        if (screenType == DEBUG)
        {
            debugScreen->update(totalUnfilteredDistance, unfilteredUpdateCount, actualUpdateCount);
        }
    }
};
