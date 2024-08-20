#pragma once

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <boards.h>
#include <Arduino.h>
#include <font_prazo_9.h>
#include <ui/screencoordinator.h>
#include <ui/mainscreen.h>
#include <ui/sleepscreen.h>

enum ScreenType
{
    SLEEP,
    MAIN,
};

class ScreenCoordinator
{
private:
    MainScreen *mainScreen = nullptr;
    SleepScreen *sleepScreen = nullptr;
    volatile ScreenType screenType;
    GxIO_Class io;
    GxEPD_Class *display;

public:
    ScreenCoordinator() : io(SPI, EPD_CS, EPD_DC, EPD_RSET)
    {
        SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);
        display = new GxEPD_Class(io, EPD_RSET, EPD_BUSY);
        display->init();
        display->setTextSize(2);
        display->setRotation(1);
        mainScreen = new MainScreen(display);
        sleepScreen = new SleepScreen(display);
        display->fillScreen(GxEPD_WHITE);
        display->update();
    };
    void switchToMainScreen(float batteryLevel, int pressCount)
    {
        this->screenType = MAIN;
        display->fillScreen(GxEPD_WHITE);
        mainScreen->init(batteryLevel, pressCount);
    }

    void updateMainScreen(float batteryLevel, int pressCount)
    {
        if (screenType == MAIN)
        {
            display->fillScreen(GxEPD_WHITE);
            mainScreen->update(batteryLevel, pressCount);
        }
    }
    void switchToSleepScreen()
    {
        screenType = SLEEP;
        display->fillScreen(GxEPD_WHITE);
        display->update();
        sleepScreen->init();
    };
};