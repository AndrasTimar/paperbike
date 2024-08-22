#pragma once

#include <string>
#include <ui/size.h>

struct PaddingValues {
    int paddingStart;
    int paddingTop;
    PaddingValues(int paddingStart, int paddingTop) : paddingStart(paddingStart), paddingTop(paddingTop) {}

    bool operator==(const PaddingValues& other) const {
        return paddingStart == other.paddingStart && paddingTop == other.paddingTop;
    }
};

struct Position {
    int x;
    int y;
    Position(int x, int y) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

struct PositionConfig {
public:
    Position position;
    Size size;
    PaddingValues paddingValues;

    PositionConfig(Position position, Size size, PaddingValues paddingValues) : position(position), size(size), paddingValues(paddingValues) {}

    bool operator==(const PositionConfig& other) const {
        return position == other.position && size == other.size && paddingValues == other.paddingValues;
    }

    bool operator!=(const PositionConfig& other) const {
        return !(*this == other);
    }
};

