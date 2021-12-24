/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <tools/DelayTimer.h>

class Button
{
  public:
    Button(const int inputPin);

    void       Init();
    const bool IsPressed();

  private:
    const int  inputPin;
    bool       state;
    DelayTimer nextUpdate;
};
