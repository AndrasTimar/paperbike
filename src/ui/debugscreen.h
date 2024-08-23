#pragma once
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <map>
#include <ui/widgets/textwidget.h>
#include <ui/widgets/positionconfig.h>
#include <boards.h>
#include <ui/size.h>

class DebugScreen
{
public:
//Deconstructor

    ~DebugScreen()
    {
        delete totalDistanceUnfilteredText;
        delete averageDistanceUnfiltered;
        delete unfilteredUpdateCountText;
        delete actualUpdateCountText;
    };
    
    DebugScreen(GxEPD_Class *display)
    {
        this->display = display;
    }

    void init()
    {
        totalDistanceUnfilteredText = TextWidgetBuilder()
            .setPosition(2, 10)
            .setSize((SCREEN_WIDTH - 10), 20)
            .setPadding(4, 8)
            .setText("Loading")
            .setTextSize(1)
            .build();

        averageDistanceUnfiltered = TextWidgetBuilder()
            .setPosition(2, 30)
            .setSize((SCREEN_WIDTH - 10), 20)
            .setPadding(4, 8)
            .setText("Loading")
            .setTextSize(1)
            .build();


        unfilteredUpdateCountText = TextWidgetBuilder()
            .setPosition(2, 50)
            .setSize((SCREEN_WIDTH - 10), 20)
            .setPadding(4, 8)
            .setText("Loading")
            .setTextSize(1)
            .build();

        actualUpdateCountText = TextWidgetBuilder()
            .setPosition(2, 70)
            .setSize((SCREEN_WIDTH - 10), 20)
            .setPadding(4, 8)
            .setText("Loading")
            .setTextSize(1)
            .build();

        totalDistanceUnfilteredText->render(*display);
        averageDistanceUnfiltered->render(*display);
        unfilteredUpdateCountText->render(*display);
    }

    void update(float totalUnfilteredDistance, int unfilteredUpdateCount, int actualUpdateCount)
    {
        totalDistanceUnfilteredText->setText("Total distance: " + String(totalUnfilteredDistance, 2));
        if(unfilteredUpdateCount > 0) {
            averageDistanceUnfiltered->setText("Average distance: " + String(totalUnfilteredDistance / unfilteredUpdateCount, 1));
        }
        unfilteredUpdateCountText->setText(String(unfilteredUpdateCount) + " updates");

        actualUpdateCountText->setText(String(actualUpdateCount) + " true updates");
        
        totalDistanceUnfilteredText->render(*display);
        averageDistanceUnfiltered->render(*display);
        unfilteredUpdateCountText->render(*display);
        actualUpdateCountText->render(*display);
    };

private:
    GxEPD_Class *display;
    TextWidget *totalDistanceUnfilteredText;
    TextWidget *averageDistanceUnfiltered;
    TextWidget *unfilteredUpdateCountText;
    TextWidget *actualUpdateCountText;
};