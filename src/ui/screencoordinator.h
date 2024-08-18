#ifndef DISPLAY_H
#define DISPLAY_H

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <ui/mainscreen.h>
#include <ui/sleepscreen.h>

enum ScreenType {
    SLEEP,
    MAIN,
};

class ScreenCoordinator {
private:
    MainScreen* mainScreen = nullptr;
    SleepScreen* sleepScreen = nullptr;
    GxIO_Class io;
    GxEPD_Class* display;
public:
    ScreenCoordinator();
    ScreenType screenType;
    void showMainScreen(float batteryLevel, int pressCount);
    void showSleepScreen();
};


#endif