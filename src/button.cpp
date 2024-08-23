#include "Arduino.h"
#include "AceButton.h"
#include "boards.h"
#include "button.h"
using namespace ace_button;

ButtonConfig config1;
AceButton button1(&config1, BUTTON_1);

ButtonCallback button1SinglePress = nullptr;
ButtonCallback button1DoublePress = nullptr;
ButtonCallback button1LongPress = nullptr;

void handleEvent(AceButton *, uint8_t event, uint8_t state)
{
    switch (event)
    {
        case AceButton::kEventClicked:
            if (button1SinglePress != nullptr)
                button1SinglePress();
            break;
        case AceButton::kEventDoubleClicked:
            if (button1DoublePress != nullptr)
                button1DoublePress();
            break;

        case AceButton::kEventLongPressed:
            if (button1LongPress != nullptr)
                button1LongPress();
            break;
    }
}

void setupButton(ButtonCallback singlePress, ButtonCallback doublePress, ButtonCallback longPress)
{
    button1SinglePress = singlePress;
    button1DoublePress = doublePress;
    button1LongPress = longPress;
    ButtonConfig *buttonConfig = button1.getButtonConfig();
    buttonConfig->setFeature(ButtonConfig::kFeatureClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
    buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
    buttonConfig->setFeature(ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);
    
    buttonConfig->setEventHandler(handleEvent);
    pinMode(BUTTON_1, INPUT_PULLUP);
    button1.init(BUTTON_1);
}

void checkButton()
{
    button1.check();
}