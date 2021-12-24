/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "IoOutput.h"
#include "LedButton.h"

class Gates
{
  public:
    Gates(IoOutput& output);

    void       Init();
    void       Check(const bool canMove);
    const bool IsOpen();

  private:
    void SetOpen(const bool open);

    LedButton button;
    bool      opened;
    bool      buttonPressed;
    IoOutput& output;
};
