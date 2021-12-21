/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Button.h"
#include "Arduino.h"

Button::Button(const int inputPin) :
    inputPin(inputPin),
    state(false),
    nextUpdate(0)
{
    pinMode(inputPin, INPUT_PULLUP);
}

void Button::Init()
{
    pinMode(inputPin, INPUT_PULLUP);
}

const bool Button::IsPressed()
{
    const bool newState = !digitalRead(inputPin);
    if (newState != state)
    {
        if (millis() > nextUpdate)
        {
            state      = newState;
            nextUpdate = millis() + 100;
            return state;
        }
    }
    return false;
}
