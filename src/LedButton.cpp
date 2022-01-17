/*************************************************************
* Created by J. Weij
*************************************************************/

#include "LedButton.h"
#include "Arduino.h"

LedButton::LedButton(const int inputPin, const int ledPin) :
    Button(inputPin),
    ledPin(ledPin),
    blinkTimer()
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

void LedButton::BlinkStop()
{
    if (blinkTimer.IsRunning())
    {
        blinkTimer.Stop();
        SetLed(false);
    }
}

void LedButton::Blink()
{
    static bool blinkState = true;
    if (!blinkTimer.IsRunning())
    {
        blinkState = true;
        blinkTimer.Start(700);
        SetLed(blinkState);
    }

    if (blinkTimer.Finished())
    {
        blinkState = !blinkState;
        blinkTimer.ReStart();
        SetLed(blinkState);
    }
}
