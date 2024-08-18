#pragma once

#include <string>

struct WidgetConfig {
public:
    int x;
    int y;
    int width;
    int height;
    int paddingStart;
    int paddingTop;

    WidgetConfig(int x, int y, int paddingStart, int paddingTop, int width, int height)
        : x(x), y(y), paddingStart(paddingStart), paddingTop(paddingTop), width(width), height(height) {}

    bool operator==(const WidgetConfig& other) const {
        return x == other.x 
                && y == other.y 
                && paddingStart == other.paddingStart 
                && paddingTop == other.paddingTop
                && width == other.width 
                && height == other.height;
    }

    bool operator!=(const WidgetConfig& other) const {
        return !(*this == other);
    }
};
