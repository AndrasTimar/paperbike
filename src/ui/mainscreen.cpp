#include <Arduino.h>
#include <ui/windowportion.h>
#include <map>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <boards.h>
#include <font_prazo_9.h>
#include <ui/mainscreen.h>
#include <ui/widgets/textwidget.h>
#include <ui/widgets/iconwidget.h>
#include <ui/widgets/widget.h>
#include <ui/widgets/widgetconfig.h>
#include <memory>
#include <utility>

MainScreen::MainScreen(GxEPD_Class* display) {
    Serial.println("Creating MainScreen");
    this->display = display;
    Serial.print("Creating window portions map");
    // WindowPortion batteryPortion = WindowPortion(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2, true);
    // WindowPortion pressCountPortion = WindowPortion(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, true);
    // windowPortionsMap.emplace("battery", batteryPortion);
    // windowPortionsMap.emplace("pressCount", pressCountPortion);
};



// void MainScreen::displayText(String text, int x, int y) {
//     display->setTextColor(GxEPD_BLACK);
//     //add to y coordinate because of custom font
//     display->setCursor(x, y + 29 / 2);
//     display->println(text);
// }

void MainScreen::init(float batteryLevel, int pressCount) {
    Serial.println("Initializing MainScreen");
    display->fillScreen(GxEPD_WHITE);
    update(batteryLevel, pressCount);
}

// void MainScreen::updateBatteryPercent(float batteryLevel) {
//     WindowPortion batteryPortion = windowPortionsMap.find("battery")->second;
//     display->setRotation(batteryPortion.usingRotation ? 1 : 0);
//     display->fillRect(batteryPortion.x, batteryPortion.y, batteryPortion.w, batteryPortion.h, GxEPD_WHITE);
//     display->drawRect(batteryPortion.x, batteryPortion.y, batteryPortion.w, batteryPortion.h, GxEPD_BLACK);
//     if (batteryLevel < 0) {
//         displayText("Charging", batteryPortion.x + 2, batteryPortion.y + 2);
//     }
//     else {
//         displayText(String(batteryLevel) + "%", batteryPortion.x + 2, batteryPortion.y + 2);
//     }
//     lastShownPercent = batteryLevel;
// }

// void MainScreen::updatePressCount(int pressCount) {
//     Serial.println("Updating press count portion");
//     WindowPortion pressCountPortion = windowPortionsMap.find("pressCount")->second;
//     display->setRotation(pressCountPortion.usingRotation ? 1 : 0);
//     display->fillRect(pressCountPortion.x, pressCountPortion.y, pressCountPortion.w, pressCountPortion.h, GxEPD_WHITE);
//     display->drawRect(pressCountPortion.x, pressCountPortion.y, pressCountPortion.w, pressCountPortion.h, GxEPD_BLACK);
//     displayText(String(pressCount) + " presses", pressCountPortion.x + 2, pressCountPortion.y + 2);
//     lastPressCount = pressCount;
// }

void MainScreen::update(float batteryLevel, int pressCount)
{
        // Create a TextWidget
        WidgetConfig textConfig(0, 40, 2, 2, "text1");
        TextWidget* textWidget = new TextWidget(textConfig, std::to_string(pressCount));

        WidgetConfig textConfig2(0, 80, 2, 2, "text1");
        TextWidget* textWidget2 = new TextWidget(textConfig2, "This is the second text widget");
        std::unique_ptr<Widget> textWidgetPtr(textWidget);
        std::unique_ptr<Widget> textWidgetPtr2(textWidget2);
        // Build the widget tree
        textWidget->addChild(std::move(textWidgetPtr2));
        widgetTree.setRoot(std::move(textWidgetPtr));
        widgetTree.updateAndRender(*display);
};