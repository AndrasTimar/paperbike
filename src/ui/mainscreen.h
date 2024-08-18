#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <map>
#include <ui/windowportion.h>

class MainScreen {
    public:
        MainScreen(GxEPD_Class* display);
        void update(float batteryLevel, int pressCount);
        void init(float batteryLevel, int pressCount);
    private:
        float lastShownPercent = -2;
        float lastPressCount = -1;
        GxEPD_Class* display;
        void displayText(String text, int x, int y);
        void updateBatteryPercent(float batteryLevel);
        void updatePressCount(int pressCount);
        std::map<std::string, WindowPortion> windowPortionsMap = std::map<std::string, WindowPortion>();
        void writeTextToPortion(String text, WindowPortion portion, int paddingX, int paddingY);
};

#endif