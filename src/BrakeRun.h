/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <tools/DelayTimer.h>
#include <tools/Logger.h>

#include "Block.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "TrackSwitch.h"

struct BrakeRunIds
{
    const int          approachLed;
    const int          blockedLed;
    const int          overridePin;
    const NodeLib::Id& blockDevice;
    const NodeLib::Id& onTrainEnter;
    const NodeLib::Id& onTrainSet;
    const NodeLib::Id& onTrainCleared;
};

class BrakeRun : public Block
{
  public:
    BrakeRun(IoOutput& outputHandler, IoInput& inputHandler, BrakeRunIds& nodeIds, const TrackSwitch& exitSwitch, const bool isStorage);
    ~BrakeRun() {}

    void Loop();

    void OnTrainApproaching();
    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();
    void OnTrainCleared();
    void OnNextBlockFreed();
    bool IsNextFree() override;

  private:
    const TrackSwitch& exitSwitch;
    const bool         isStorage;
    DelayTimer         delayRelease;
};
