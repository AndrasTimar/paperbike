#pragma once
#include <ui/widgets/widget.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <vector>
#include <memory>
#include <Arduino.h>
#include <ui/size.h>
#include <ui/widgets/positionconfig.h>

class IconWidget : public Widget {
public:
    IconWidget(const PositionConfig config, const uint8_t* iconData, const Size iconSize)
        : Widget(config), iconData(iconData), iconSize(iconSize) {}

    void renderToCanvas(GFXcanvas1 &canvas, PaddingValues paddingValues) const override {
        canvas.drawBitmap(paddingValues.paddingStart, paddingValues.paddingTop, iconData, iconSize.width, iconSize.height, 1);
    }

    void setIcon(const uint8_t* iconData) {
        this->iconData = iconData;
        markDirty();
    }
private:
    const uint8_t* iconData;
    const Size iconSize;
};