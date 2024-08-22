#pragma once
#include <ui/widgets/positionconfig.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <vector>
#include <memory>
#include <string>
#include <boards.h>

class Widget {
public:
    Widget(const PositionConfig config)
        : config(config), dirty(true), canvas(config.size.width, config.size.height){}

    virtual ~Widget() {}

    void render(GxEPD_Class &display) {
        if(!dirty) {
            return;
        }
        GFXcanvas1 canvas(config.size.width, config.size.height);
        renderToCanvas(canvas, config.paddingValues);

        display.fillRect(config.position.x, config.position.y, config.size.width, config.size.height, GxEPD_WHITE);
        display.drawBitmap(config.position.x, config.position.y, canvas.getBuffer(), config.size.width, config.size.height, GxEPD_BLACK);
        if(DEBUG_MODE) {
            display.drawRect(config.position.x, config.position.y, config.size.width, config.size.height, GxEPD_BLACK);
        }
        display.updateWindow(config.position.x, config.position.y, config.size.width, config.size.height, true);
        dirty = false;
    }

    virtual void renderToCanvas(GFXcanvas1 &canvas, PaddingValues paddingValues) const = 0;

    void markDirty() {
        dirty = true;
    }

    bool isDirty() const {
        return dirty;
    }
   
protected:
    bool dirty;
    PositionConfig config;
    GFXcanvas1 canvas;
    bool showBorder = true;
};

