#ifndef WINDOW_PORTION_H
#define WINDOW_PORTION_H
#include <Arduino.h>

class WindowPortion {
    
    public:
        int x;
        int y;
        int w;
        int h;
        bool usingRotation;
        WindowPortion(int x, int y, int w, int h, bool usingRotation);
};
#endif