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


class TextWidgetBuilder {
private:
    Position position;
    Size size;
    PaddingValues padding;
    String text;
    int textSize;

public:
    TextWidgetBuilder():  position(0, 0), size(SCREEN_WIDTH, 30), padding(2, 2), text(""), textSize(2)  {}

    TextWidgetBuilder& setPosition(int x, int y) {
        position = Position(x, y);
        return *this;
    }

    TextWidgetBuilder& setSize(int width, int height) {
        size = Size(width, height);
        return *this;
    }

    TextWidgetBuilder& setPadding(int left, int top) {
        padding = PaddingValues(left, top);
        return *this;
    }

    TextWidgetBuilder& setText(const String newText) {
        text = newText;
        return *this;
    }

    TextWidgetBuilder& setTextSize(int newSize) {
        textSize = newSize;
        return *this;
    }

    TextWidget* build() const {
        return new TextWidget(PositionConfig(position, size, padding), text, textSize);
    }
};