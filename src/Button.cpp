/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Button.h"
#include "Arduino.h"

Button::Button(const int inputPin) :
    inputPin(inputPin),
    state(false),
    nextUpdate()
{
    Init();
}

void Button::Init()
{
    pinMode(inputPin, INPUT_PULLUP);
}

const bool Button::IsPressed()
{
    if (nextUpdate.Finished() || !nextUpdate.IsRunning())
    {
        const bool newState = !digitalRead(inputPin);
        if (newState != state)
        {
            state = newState;
            nextUpdate.Start(100);
        }
    }
    return state;
}
