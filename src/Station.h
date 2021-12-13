/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "Block.h"
#include "Button.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "LedButton.h"
#include <tools/Logger.h>

class Station : public Block
{
  public:
    Station(IoInput& inputHandler, IoOutput& outputHandler);
    ~Station() { }

    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();
    void OnNextBlockFreed();

    void Init();
    void Loop();

  private:
    bool dispatchOk;
    LedButton dispatchButton;
    unsigned long nextAction;
};
