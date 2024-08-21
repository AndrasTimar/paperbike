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

    void init(float batteryLevel, int pressCount, float magnetPassCount)
    {
        batteryText = new TextWidget(WidgetConfig(2, 10, 2, 2, SCREEN_WIDTH - 10, 20), "Battery: -%");
        counterText = new TextWidget(WidgetConfig(2, 40, 2, 2, SCREEN_WIDTH - 10, 20), "Presses: -");
        magnetText = new TextWidget(WidgetConfig(2, 70, 2, 2, SCREEN_WIDTH - 10, 20), "Magnet: -");
        update(batteryLevel, pressCount, magnetPassCount);
    }

    void update(float batteryLevel, int pressCount, float magnetPassCount)
    {
        int level = roundToNearestFive(batteryLevel);
        batteryText->setText(String("Battery: " + String(batteryLevel) + " %"));
        counterText->setText(String("Presses " + String(pressCount)));
        magnetText->setText(String("Speed: " + String(magnetPassCount)) + " km/h");

        batteryText->render(*display, true);
        counterText->render(*display, true);
        magnetText->render(*display, true);
    };

    int roundToNearestFive(float num)
    {
        return (int)(round(num / 5.0) * 5.0);
    }

private:
    GxEPD_Class *display;
    TextWidget *batteryText;
    TextWidget *counterText;
    TextWidget *magnetText;
};