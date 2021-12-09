/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

class Button
{
  public:
    Button(const int inputPin);

    void Init();
    const bool IsPressed();

  private:
    const int inputPin;
    bool state;
    unsigned long nextUpdate;
};
