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
    TextWidget(const WidgetConfig config, const String text)
        : Widget(config), text(text) {}

    void setText(const String newText) {
        // if text is the same return
        if (this->text == newText) {
            return;
        }
        
        Serial.println("Setting text");
        this->text = newText;
        markDirty();
    }

    void renderToCanvas(GFXcanvas1 &canvas) const override {
        canvas.setTextSize(2);
        canvas.setTextColor(1);
        //TODO get font from outside
        // canvas.setFont(&FreeMonoBold9pt7b);
        // display.setFont(&FreeMonoBold9pt7b);
        //get the text bounds
        canvas.setCursor(config.paddingStart, config.paddingTop);
        canvas.print(text);
    }

private:
    String text;
};
