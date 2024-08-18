#pragma once
#include <ui/widgets/widgetconfig.h>
#include <GxDEPG0213BN/GxDEPG0213BN.h>
#include <vector>
#include <memory>

#include <memory>
#include <vector>
#include <string>
#include <memory>
#include <vector>
#include <string>

class Widget {
public:
    Widget(const WidgetConfig& config)
        : config(config), dirty(true){}

    virtual ~Widget() {}

    virtual void render(GxEPD_Class &display) const = 0; // Const method

    void markDirty() {
        dirty = true;
    }

    bool isDirty() const {
        return dirty;
    }

    void updateAndRender(GxEPD_Class &display) {
        if (isDirty()) {
            render(display); // Call const render method
            dirty = false;
        }
    }

    // void setPosition(int x, int y) {
    //     globalX = x;
    //     globalY = y;
    //     markDirty();
    // }

    void addChild(std::unique_ptr<Widget> child) {
        children.push_back(std::move(child));
    }

    const std::vector<std::unique_ptr<Widget>>& getChildren() const {
        return children;
    }

    const WidgetConfig& getConfig() const {
        return config;
    }

    virtual bool hasChanged(const Widget& other) const {
        return config != other.getConfig();
    }

    virtual std::unique_ptr<Widget> clone() const = 0; // Pure virtual method
    virtual const char* getType() const = 0; // New method for type identification
   
protected:
    WidgetConfig config;
    bool dirty;
    std::vector<std::unique_ptr<Widget>> children;
};

