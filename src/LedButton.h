/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "Button.h"

class LedButton : public Button
{
  public:
    LedButton(const int inputPin, const int ledPin);

    void Init();
    void SetLed(const bool state);

  private:
    const int ledPin;
};
