/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "Block.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "Logger.h"

class StorageTrack : public Block
{
  public:
    StorageTrack(IoOutput& outputHandler);
    ~StorageTrack() { }

    void OnTrainApproaching();
    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet(bool exitStorage, bool nextFree);
    void OnNextBlockFreed();

  private:
};
