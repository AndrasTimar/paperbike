#include <ui/windowportion.h>
#include <boards.h>

WindowPortion::WindowPortion(int x, int y, int w, int h, bool usingRotation) {
    this->x = x;
    this->y = y + UNUSABLE_TOP_HEIGHT;
    this->w = w;
    this->h = h;
    this->usingRotation = usingRotation;
}