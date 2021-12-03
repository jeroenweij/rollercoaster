/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "Block.h"
#include "IoInput.h"
#include "IoOutput.h"
#include "Logger.h"
#include "StorageTrack.h"

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

    void OnEnterSwitchChanged(const Value& value);
    void OnExitSwitchChanged(const Value& value);

    bool SetEnterSwitch(bool value);
    bool SetExitSwitch(bool value);

    bool IsApproaching() override;
    bool IsFree() override;

  private:
    void SetSwitches();

    bool enterStorage;
    bool exitStorage;
    void Release();
    StorageTrack storage;
};
