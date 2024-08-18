#pragma once
#include <ui/widgets/widget.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <vector>
#include <memory>
#include <Arduino.h>
#include <ui/size.h>

class IconWidget : public Widget {
public:
    IconWidget(const WidgetConfig config, const uint8_t* iconData, const Size iconSize)
        : Widget(config), iconData(iconData), iconSize(iconSize) {}

    void renderToCanvas(GFXcanvas1 &canvas) const override {
        Serial.println("Rendering icon");
        canvas.drawBitmap(config.paddingStart, config.paddingTop, iconData, iconSize.width, iconSize.height, 1);
    }

    void setIcon(const uint8_t* iconData) {
        this->iconData = iconData;
        markDirty();
    }
private:
    const uint8_t* iconData;
    const Size iconSize;
};