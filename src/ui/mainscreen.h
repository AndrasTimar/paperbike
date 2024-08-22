#pragma once
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <map>
#include <ui/widgets/textwidget.h>
#include <ui/widgets/positionconfig.h>
#include <boards.h>
#include <ui/size.h>

class MainScreen
{
public:
//Deconstructor

    ~MainScreen()
    {
        delete batteryText;
        delete speedText;
    };
    
    MainScreen(GxEPD_Class *display)
    {
        this->display = display;
    }

    void init()
    {

        batteryText = new TextWidget(PositionConfig(Position(2, 10), Size((SCREEN_WIDTH - 10) / 2, 20), PaddingValues(2, 2)), "-%", 2);
        distanceText = new TextWidget(PositionConfig(Position((SCREEN_WIDTH - 10) / 2 + 40, 10), Size(SCREEN_WIDTH - 10 / 2, 20), PaddingValues(2, 2)), "Loading...", 2);
        speedText = new TextWidget(PositionConfig(Position(2, 30), Size(SCREEN_WIDTH - 10, 70), PaddingValues(40, 20)), "Loading...", 3);

        batteryText->render(*display);
        speedText->render(*display);
        distanceText->render(*display);
    }

    void update(float batteryLevel, double speedKmph, double totalDistance)
    {
        int level = roundToNearestFive(batteryLevel);
        batteryText->setText(String(String(level) + " %"));
        speedText->setText(String(speedKmph) + " km/h");
        distanceText->setText(String(totalDistance / 1000) + " km");

        batteryText->render(*display);
        speedText->render(*display);
        distanceText->render(*display);
    };

    int roundToNearestFive(float num)
    {
        return (int)(round(num / 5.0) * 5.0);
    }

private:
    GxEPD_Class *display;
    TextWidget *batteryText;
    TextWidget *speedText;
    TextWidget *distanceText;
};