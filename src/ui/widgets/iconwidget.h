#pragma once
#include <ui/widgets/widgetconfig.h>
#include <ui/widgets/widget.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <vector>
#include <memory>

class IconWidget : public Widget {
public:
    IconWidget(const WidgetConfig& config, const uint8_t* iconData)
        : Widget(config), iconData(iconData) {}

    void render(GxEPD_Class &display) const override {
        // Render icon using display
        // Example: display.drawBitmap(localX, localY, iconData, iconWidth, iconHeight, GxEPD_WHITE);
    }

    std::unique_ptr<Widget> clone() const override {
        auto clone = std::unique_ptr<IconWidget>(new IconWidget(config, iconData));
        for (const auto& child : getChildren()) {
            clone->addChild(child->clone());
        }
        return std::unique_ptr<Widget>(clone.release());
    }
    virtual const char* getType() const {
        return "IconWidget";
     }; // New method for type identification
   

private:
    const uint8_t* iconData;
};