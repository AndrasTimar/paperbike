#include "Arduino.h"
#include "AceButton.h"
#include "boards.h"
#include "button.h"
using namespace ace_button;

ButtonConfig config1;
AceButton button1(&config1, BUTTON_1);

ButtonCallback button1Callback = nullptr;

void handleEvent(AceButton*, uint8_t event, uint8_t state) {
    Serial.print("handleEvent: ");
    Serial.print("eventType: ");
    Serial.print(event);
    if(button1Callback != nullptr){
        if (event != ace_button::AceButton::kEventClicked && event != ace_button::AceButton::kEventLongPressed)
        {
            if (state == 1)
            {
                button1Callback();
            }
        }
    }
}

void setupButton(ButtonCallback callback) {
    button1Callback = callback;
    ButtonConfig* buttonConfig = button1.getButtonConfig();
    buttonConfig->setEventHandler(handleEvent);
    pinMode(BUTTON_1, INPUT_PULLUP);
    button1.init(BUTTON_1);
    Serial.println("setupButton");
}

void checkButton(){
    button1.check();
}