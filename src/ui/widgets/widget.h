#pragma once
#include <ui/widgets/widgetconfig.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <vector>
#include <memory>
#include <string>

class Widget {
public:
    Widget(const WidgetConfig config)
        : config(config), dirty(true), canvas(config.width, config.height){}

    virtual ~Widget() {}

    void render(GxEPD_Class &display, bool update) {
        if(!dirty) {
            return;
        }
        Serial.println("Rendering widget");
        GFXcanvas1 canvas(config.width, config.height);
        renderToCanvas(canvas);

        display.fillRect(config.x, config.y, config.width, config.height, GxEPD_WHITE);
        display.drawBitmap(config.x, config.y, canvas.getBuffer(), config.width, config.height, GxEPD_BLACK);
        if(showBorder) {
            display.drawRect(config.x, config.y, config.width, config.height, GxEPD_BLACK);
        }
        if (update) {
          display.updateWindow(config.x, config.y, config.width, config.height, true);
        }
        dirty = false;
    }

    virtual void renderToCanvas(GFXcanvas1 &canvas) const = 0; // Const method

    void markDirty() {
        dirty = true;
    }

    bool isDirty() const {
        return dirty;
    }
   
protected:
    bool dirty;
    WidgetConfig config;
    GFXcanvas1 canvas;
    bool showBorder = true;
};

