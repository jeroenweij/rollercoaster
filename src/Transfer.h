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

    // IBlock implementation
    bool IsFree() override;
    void Restart() override;
    void OnTrainApproaching() override;
    void Reset() override;

    void OnTrainLeft();
    void OnNextBlockFreed();
    void SetNextBlock(IBlock* block);
    void SwitchChanged();
    bool IsExpectingorEntered();

    bool EnterSwitchSafeToMove();
    bool ExitSwitchSafeToMove();

    const int CountTrains();

  private:
    TrackSwitch enterStorage;
    TrackSwitch exitStorage;
    BrakeRun    brakeRun;
    BrakeRun    storage;
    Lift&       lift;
};
