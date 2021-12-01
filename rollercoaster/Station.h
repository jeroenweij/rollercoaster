/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "Logger.h"
#include "Block.h"
#include "IoInput.h"
#include "IoOutput.h"

class Station : public Block
{
public:
    Station(IoInput& inputHandler, IoOutput& outputHandler);
    ~Station() {}

    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();
    void OnNextBlockFreed();

private:
};
