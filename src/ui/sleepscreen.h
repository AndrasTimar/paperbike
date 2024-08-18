#ifndef SLEEPSCREEN_H
#define SLEEPSCREEN_H

#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <map>
#include <Arduino.h>
#include <map>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <bitmaps.h>
#include <ui/sleepscreen.h>
#include <boards.h>
#include <ui/widgets/iconwidget.h>

class SleepScreen
{
public:
    SleepScreen(GxEPD_Class *display) : display(display) {
        int width = SCREEN_WIDTH;
        int height = SCREEN_HEIGHT;
        int paddingStartForCenter = ((width - sleepIconSize.width) / 2);
        int paddingTopForCenter = ((height - sleepIconSize.height) / 2);
        iconWidget = new IconWidget(WidgetConfig(0, 0, paddingStartForCenter, paddingTopForCenter, width, height), sleepIconData, sleepIconSize);
    };
    void show()
    {
        display->fillScreen(GxEPD_WHITE);
        iconWidget->render(*display, false);
        display->update();
    }

private:
    ~SleepScreen()
    {
        delete iconWidget;
    }
    GxEPD_Class *display;
    IconWidget *iconWidget;
};

#endif