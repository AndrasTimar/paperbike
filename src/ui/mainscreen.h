#pragma once
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <map>
#include <ui/widgets/textwidget.h>
#include <ui/widgets/widgetconfig.h>
#include <boards.h>

class MainScreen
{
public:
//Deconstructor

    ~MainScreen()
    {
        delete batteryText;
        delete counterText;
    };
    
    MainScreen(GxEPD_Class *display)
    {
        Serial.println("Creating MainScreen");
        this->display = display;
    }

    void init(float batteryLevel, int pressCount)
    {
        batteryText = new TextWidget(WidgetConfig(2, 10, 2, 2, SCREEN_WIDTH - 10, 40), "Battery: -%");
        counterText = new TextWidget(WidgetConfig(2, 60, 2, 2, SCREEN_WIDTH - 10, 40), "Presses: -");
        update(batteryLevel, pressCount);
    }

    void update(float batteryLevel, int pressCount)
    {
        int level = roundToNearestFive(batteryLevel);
        batteryText->setText(String("Battery: " + String(batteryLevel) + " %"));
        Serial.println("Updating MainScreen batteryLevel level: " + String(level));
        counterText->setText(String("Pressed button " + String(pressCount) + " times"));

        batteryText->render(*display, true);
        counterText->render(*display, true);
    };

    int roundToNearestFive(float num)
    {
        return (int)(round(num / 5.0) * 5.0);
    }

private:
    GxEPD_Class *display;
    TextWidget *batteryText;
    TextWidget *counterText;
};