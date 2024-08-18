#pragma once

#include <string>

class WidgetConfig {
public:
    int globalX;
    int globalY;
    int paddingStart;
    int paddingTop;
    std::string id; // Unique identifier for the widget

    WidgetConfig(int x, int y, int paddingStart, int paddingTop, const std::string& id)
        : globalX(x), globalY(y), id(id), paddingStart(paddingStart), paddingTop(paddingTop) {}

    bool operator==(const WidgetConfig& other) const {
        return id == other.id && globalX == other.globalX && globalY == other.globalY && paddingStart == other.paddingStart && paddingTop == other.paddingTop;
    }

    bool operator!=(const WidgetConfig& other) const {
        return !(*this == other);
    }

    // For debugging
    std::string toString() const {
        return "ID: " + id + ", X: " + std::to_string(globalX) + ", Y: " + std::to_string(globalY);
    }
};
