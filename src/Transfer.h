/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <tools/Logger.h>

#include "IBlock.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "BrakeRun.h"
#include "TrackSwitch.h"
#include "Lift.h"

class Transfer : public IBlock
{
  public:
    Transfer(IoInput& inputHandler, IoOutput& outputHandler, Lift& lift);
    ~Transfer() { }

    void OnTrainApproaching();
    void OnTrainLeft();
    void OnNextBlockFreed();
    void SetNextBlock(IBlock* block);
    void SwitchChanged();

    bool IsApproaching();
    bool IsFree() override;

    bool EnterSwitchSafeToMove();
    bool ExitSwitchSafeToMove();

  private:

    TrackSwitch enterStorage;
    TrackSwitch exitStorage;
    BrakeRun brakeRun;
    BrakeRun storage;
    Lift &lift;
};
