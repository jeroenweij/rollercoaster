/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "Button.h"
#include "tools/DelayTimer.h"

class LedButton : public Button
{
  public:
    LedButton(const int inputPin, const int ledPin);

    void Init();
    void SetLed(const bool state);
    void Blink();
    void BlinkStop();

  private:
    const int  ledPin;
    DelayTimer blinkTimer;
};
