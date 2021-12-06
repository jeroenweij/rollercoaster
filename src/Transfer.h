/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <tools/Logger.h>

#include "Block.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "StorageTrack.h"
#include "TrackSwitch.h"

class Transfer : public Block
{
  public:
    Transfer(IoInput& inputHandler, IoOutput& outputHandler);
    ~Transfer() { }

    void OnStorageTrainSet();
    void OnTrainApproaching();
    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();
    void OnNextBlockFreed();

    bool IsApproaching() override;
    bool IsFree() override;

    bool EnterSwitchSafeToMove();
    bool ExitSwitchSafeToMove();

  private:
    void Release();

    TrackSwitch enterStorage;
    TrackSwitch exitStorage;
    StorageTrack storage;
};
