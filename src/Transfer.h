/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <tools/Logger.h>

#include "BrakeRun.h"
#include "IBlock.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "Lift.h"
#include "TrackSwitch.h"

class Transfer : public IBlock
{
  public:
    Transfer(IoInput& inputHandler, IoOutput& outputHandler, Lift& lift);
    ~Transfer() {}
    void Init();
    void Loop();

    void OnTrainApproaching() override;
    void OnTrainLeft();
    void OnNextBlockFreed();
    void SetNextBlock(IBlock* block);
    void SwitchChanged();

    bool IsApproaching();
    bool IsFree() override;
    void ResetStop() override;

    bool EnterSwitchSafeToMove();
    bool ExitSwitchSafeToMove();

  private:
    TrackSwitch enterStorage;
    TrackSwitch exitStorage;
    BrakeRun    brakeRun;
    BrakeRun    storage;
    Lift&       lift;
};
