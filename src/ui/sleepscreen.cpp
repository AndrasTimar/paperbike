
#include <Arduino.h>
#include <ui/windowportion.h>
#include <map>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <bitmaps.h>
#include <ui/sleepscreen.h>
#include <boards.h>

SleepScreen::SleepScreen(GxEPD_Class* display) {
    this->display = display;
    this->windowPortionsMap.emplace("icon", WindowPortion(0, 0, 250, 128, false));
};

void SleepScreen::show()
{
    if (windowPortionsMap.empty())
    {
        WindowPortion windowPortion = WindowPortion(0, 0, 256, 128, false);
        windowPortionsMap.emplace("icon", windowPortion);
    }
    WindowPortion iconPortion = windowPortionsMap.find("icon")->second;
    display->drawBitmap(iconPortion.x, iconPortion.y, trashcan, iconPortion.w, iconPortion.h, GxEPD_BLACK);
    display->update();
};
