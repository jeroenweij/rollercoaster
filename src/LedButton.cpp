/*************************************************************
* Created by J. Weij
*************************************************************/

#include "LedButton.h"
#include "Arduino.h"

LedButton::LedButton(const int inputPin, const int ledPin) :
    Button(inputPin),
    ledPin(ledPin)
{
    Init();
    SetLed(true);
}

void LedButton::Init()
{
    Button::Init();
    pinMode(ledPin, OUTPUT);
    SetLed(false);
}

void LedButton::SetLed(const bool state)
{
    digitalWrite(ledPin, state);
}
