
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
};

void SleepScreen::show(){
    
};
