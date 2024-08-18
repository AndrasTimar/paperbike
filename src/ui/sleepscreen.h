#ifndef SLEEPSCREEN_H
#define SLEEPSCREEN_H

#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <map>
#include <ui/windowportion.h>

class SleepScreen {
    public:
        SleepScreen(GxEPD_Class* display);
        void show();
    private:
        GxEPD_Class* display;
        // 128x256
        std::map<std::string, WindowPortion> windowPortionsMap = std::map<std::string, WindowPortion>();
};


#endif