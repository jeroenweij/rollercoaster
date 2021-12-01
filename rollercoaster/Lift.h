/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "Logger.h"
#include "Block.h"
#include "IoInput.h"
#include "IoOutput.h"

class Lift : public Block
{
public:
    Lift(IoInput& inputHandler, IoOutput& outputHandler);
    ~Lift() {}

    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();
    void OnNextBlockFreed();

private:
};
