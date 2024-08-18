#ifndef MAINSCREEN_H
#define MAINSCREEN_H
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <map>
#include <ui/widgets/widgettree.h>
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
        WidgetTree widgetTree;
};

#endif