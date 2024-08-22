#pragma once
#include <ui/widgets/positionconfig.h>
#include <ui/widgets/widget.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <vector>
#include <memory>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Arduino.h>

class TextWidget : public Widget {
public:
    TextWidget(const PositionConfig config, const String text, const int textSize = 2)
        : Widget(config), text(text), textSize(textSize) {}

    void setText(const String newText) {
        if (this->text == newText) {
            return;
        }
        
        this->text = newText;
        markDirty();
    }

    void renderToCanvas(GFXcanvas1 &canvas, PaddingValues paddingValues) const override {
        canvas.setTextSize(textSize);
        canvas.setTextColor(1);
        canvas.setCursor(paddingValues.paddingStart, paddingValues.paddingTop);
        canvas.print(text);
    }

private:
    String text;
    const int textSize;
};
