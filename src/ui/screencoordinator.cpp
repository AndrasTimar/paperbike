#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <boards.h>
#include <Arduino.h>
#include <font_prazo_9.h>
#include <ui/screencoordinator.h>
#include <ui/mainscreen.h>
#include <ui/sleepscreen.h>

ScreenCoordinator::ScreenCoordinator() : io(SPI, EPD_CS, EPD_DC, EPD_RSET){
    SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);
    display = new GxEPD_Class(io, EPD_RSET, EPD_BUSY);
    display->init();
    display->setTextSize(2);
    mainScreen = new MainScreen(display);
    sleepScreen = new SleepScreen(display);
    display->fillScreen(GxEPD_WHITE);
    display->update();
};

void ScreenCoordinator::showMainScreen(float batteryLevel, int pressCount)
{
    if (screenType != MAIN) {
        screenType = MAIN;
        display->fillScreen(GxEPD_WHITE);
        mainScreen->init(batteryLevel, pressCount);
    } else {
        mainScreen->update(batteryLevel, pressCount);
    }
}

void ScreenCoordinator::showSleepScreen(){
    if(screenType != SLEEP){
        screenType = SLEEP;
        display->fillScreen(GxEPD_WHITE);
        display->update();
    }
    sleepScreen->show();   
}