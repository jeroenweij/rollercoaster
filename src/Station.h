/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <tools/DelayTimer.h>
#include <tools/Logger.h>

#include "Block.h"
#include "Button.h"
#include "Gates.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "LedButton.h"

class Station : public Block
{
  public:
    Station(IoInput& inputHandler, IoOutput& outputHandler);
    ~Station() {}

    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();
    void OnNextBlockFreed();
    void ResetStop() override;

    void Init();
    void Loop();

  private:
    LedButton  dispatchButton;
    DelayTimer delayRelease;
    Gates      gates;
};
