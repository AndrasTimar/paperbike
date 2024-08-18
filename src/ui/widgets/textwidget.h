#pragma once
#include <ui/widgets/widgetconfig.h>
#include <ui/widgets/widget.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <vector>
#include <memory>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Arduino.h>

class TextWidget : public Widget {
public:
    TextWidget(const WidgetConfig& config, const std::string& text)
        : Widget(config), text(text) {}

    void render(GxEPD_Class &display) const override {
        int totalGlobalX = config.globalX + config.paddingStart;
        int totalGlobalY = config.globalY + config.paddingTop;
        display.setRotation(1);
        display.setTextColor(GxEPD_BLACK);
        // display.setFont(&FreeMonoBold9pt7b);
        //get the text bounds
        int16_t x1, y1;
        uint16_t w, h;
        display.getTextBounds(text.c_str(), config.globalX + config.paddingStart, config.globalY + config.paddingTop, &x1, &y1, &w, &h);
        display.fillRect(x1, y1, w, h, GxEPD_WHITE);
        Serial.println("LocalX: " + String(config.globalX) + " LocalY: " + String(config.globalY));
        display.setCursor(config.globalX + config.paddingStart, config.globalY + config.paddingTop);
        display.print(text.c_str());
        //TODO update only its own portion. Draw a white rectangle to clear the previous text
        // Needs to provide height, width, and global positions for this to work
        display.updateWindow(x1, y1, w, h, true);
    }

    std::unique_ptr<Widget> clone() const override {
        auto clone = std::unique_ptr<TextWidget>(new TextWidget(config, text));
        for (const auto& child : getChildren()) {
            clone->addChild(child->clone());
        }
        return std::unique_ptr<Widget>(clone.release());
    }

     virtual const char* getType() const {
        return "TextWidget";
     }; // New method for type identification
   
   bool hasChanged(const Widget& other) const override {
        Serial.println("Checking changes in TextWidget.");

        if (other.getType() != getType()) {
            Serial.println("Error: Type mismatch in hasChanged");
            return true; // Assume it has changed if type doesn't match
        }

        const TextWidget& otherTextWidget = static_cast<const TextWidget&>(other);
        bool hasChanged = config != other.getConfig() || text != otherTextWidget.text;

        Serial.print("Has changed: ");
        Serial.println(hasChanged ? "true" : "false");

        return hasChanged;
}

private:
    std::string text;
};
