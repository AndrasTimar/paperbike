#ifndef BUTTON_H
#define BUTTON_H
#include <Acebutton.h>
using namespace ace_button;

typedef void (*ButtonCallback)(); //Callback function type def

void setupButton(ButtonCallback singlePress, ButtonCallback doublePress, ButtonCallback longPress);

void checkButton();
#endif