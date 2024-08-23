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
        delete distanceText;
        delete averageSpeedText;
    };
    
    MainScreen(GxEPD_Class *display)
    {
        this->display = display;
    }

    void init()
    {

        batteryText = new TextWidget(PositionConfig(Position(2, 20), Size((SCREEN_WIDTH - 10) / 2, 20), PaddingValues(2, 2)), "-%", 2);
        distanceText = new TextWidget(PositionConfig(Position((SCREEN_WIDTH - 10) / 2 + 20, 20), Size((SCREEN_WIDTH - 10) / 2 - 10, 20), PaddingValues(2, 2)), "- km", 2);


        speedText = new TextWidget(PositionConfig(Position(2, 40), Size(SCREEN_WIDTH - 10, 60), PaddingValues(40, 20)), "- km/h", 3);


        averageSpeedText = new TextWidget(PositionConfig(Position(2, 100), Size((SCREEN_WIDTH - 10) / 2, 20), PaddingValues(2, 2)), "- km/h", 2);
        legTimeText = new TextWidget(PositionConfig(Position((SCREEN_WIDTH - 10) / 2 + 20, 100), Size((SCREEN_WIDTH - 10) / 2 - 10, 20), PaddingValues(2, 2)), "0:00:00", 2);

        batteryText->render(*display);
        speedText->render(*display);
        distanceText->render(*display);
        averageSpeedText->render(*display);
        legTimeText->render(*display);
    }

    void update(float batteryLevel, double speedKmph, double totalDistance, double averageSpeed, double legTimeMs)
    {
        String legTimeSeconds = String((int)(legTimeMs / 1000) % 60);
        String legTimeMinutes = String((int)(legTimeMs / (1000 * 60)) % 60);
        String legTimeHours = String((int)(legTimeMs / (1000 * 60 * 60)) % 24);

        int level = roundToNearestFive(batteryLevel);
        batteryText->setText(String(String(level) + " %"));
        speedText->setText(String(speedKmph, 1) + " km/h");
        distanceText->setText(String(totalDistance / 1000, 2) + " km");
        if(averageSpeed > 2) {
            averageSpeedText->setText(String(averageSpeed, 1) + " km/h");
        } else {
            averageSpeedText->setText("<2 km/h");
        }
        
        //set legtime text formatted to HH:mm:ss with padding
        legTimeText->setText(legTimeHours + ":" + (legTimeMinutes.length() == 1 ? "0" + legTimeMinutes : legTimeMinutes) + ":" + (legTimeSeconds.length() == 1 ? "0" + legTimeSeconds : legTimeSeconds));

        batteryText->render(*display);
        speedText->render(*display);
        distanceText->render(*display);
        averageSpeedText->render(*display);
        legTimeText->render(*display);
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
    TextWidget *averageSpeedText;
    TextWidget *legTimeText;
};