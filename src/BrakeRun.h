/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <tools/Logger.h>

#include "Block.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "TrackSwitch.h"

struct BrakeRunIds
{
    const NodeLib::Id& approachLed;
    const NodeLib::Id& blockedLed;
    const NodeLib::Id& blockDevice;
    const NodeLib::Id& onTrainEnter;
    const NodeLib::Id& onTrainSet;
};

class BrakeRun : public Block
{
  public:
    BrakeRun(IoOutput& outputHandler, IoInput inputHandler, BrakeRunIds& nodeIds, const TrackSwitch& exitSwitch, const bool isStorage);
    ~BrakeRun() { }

    void OnTrainApproaching();
    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();
    void OnNextBlockFreed();

  private:
    const TrackSwitch& exitSwitch;
    const bool isStorage;
};
