/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "Logger.h"
#include "Block.h"
#include "IoInput.h"
#include "IoOutput.h"


class StorageTrack : public Block
{
public:
    StorageTrack(IoOutput& outputHandler);
    ~StorageTrack() {}

    void OnTrainApproaching();
    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet(bool exitStorage, bool nextFree);
    void OnNextBlockFreed();

private:
};
