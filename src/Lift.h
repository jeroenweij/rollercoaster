/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "Block.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "Logger.h"

class Lift : public Block
{
  public:
    Lift(IoInput& inputHandler, IoOutput& outputHandler);
    ~Lift() { }

    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();
    void OnNextBlockFreed();

  private:
};
