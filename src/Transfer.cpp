/*************************************************************
 * Created by J. Weij
 *************************************************************/

#include "Transfer.h"
#include "IoConfig.h"
#include <pins.h>

BrakeRunIds brakeRunIds = {
    .approachLed    = PIN_UI_BRAKE_APPR,
    .blockedLed     = PIN_UI_BRAKE_BLOCK,
    .overridePin    = PIN_MANUAL_BRAKE,
    .blockDevice    = NodeId::brakerunBrake.id,
    .onTrainEnter   = NodeId::brakeRunEnter.id,
    .onTrainHalfway = NodeId::brakeRunHalfway.id,
    .onTrainSet     = NodeId::brakeRunSet.id,
    .onTrainCleared = NodeId::stationEnter.id,
};

BrakeRunIds storageTrackIds = {
    .approachLed    = PIN_UI_STORAGE_APPR,
    .blockedLed     = PIN_UI_STORAGE_BLOCK,
    .overridePin    = PIN_MANUAL_STORAGE,
    .blockDevice    = NodeId::storageBrake.id,
    .onTrainEnter   = NodeId::storageEnter.id,
    .onTrainHalfway = NodeId::storageHalfway.id,
    .onTrainSet     = NodeId::storageSet.id,
    .onTrainCleared = NodeId::stationEnter.id,
};

Transfer::Transfer(IoInput& inputHandler, IoOutput& outputHandler, Lift& lift) :
    enterStorage(outputHandler, PIN_ENTER_SWITCH, PIN_UI_ENTER_SWITCH, NodeId::transferInSwitch.id, 180, 0, *this, &Transfer::EnterSwitchSafeToMove),
    exitStorage(outputHandler, PIN_EXIT_SWITCH, PIN_UI_EXIT_SWITCH, NodeId::transferOutSwitch.id, 0, 180, *this, &Transfer::ExitSwitchSafeToMove),
    brakeRun(outputHandler, inputHandler, brakeRunIds, exitStorage, false),
    storage(outputHandler, inputHandler, storageTrackIds, exitStorage, true),
    lift(lift)
{
    inputHandler.AddCallback(NodeId::liftLeft.id, this, &Transfer::OnTrainApproaching, true);
    inputHandler.AddCallback(NodeId::stationSet.id, this, &Transfer::OnTrainLeft, true);
    inputHandler.AddCallback(NodeId::liftEnter.id, this, &Transfer::OnNextBlockFreed, true);
}

void Transfer::Init()
{
    exitStorage.Init();
    enterStorage.Init();
    storage.Init();
    brakeRun.Init();
}

void Transfer::Loop()
{
    exitStorage.Loop();
    enterStorage.Loop();
    storage.Loop();
    brakeRun.Loop();
}

void Transfer::OnTrainApproaching()
{
    LOG_INFO(F("Transfer Train Approaching"));
    if (enterStorage.IsSet())
    {
        storage.OnTrainApproaching();
    }
    else
    {
        brakeRun.OnTrainApproaching();
    }
}

void Transfer::Reset()
{
    storage.Reset();
    brakeRun.Reset();
}

void Transfer::OnTrainLeft()
{
    LOG_INFO(F("Transfer Train Left"));
    if (this->exitStorage.IsSet())
    {
        storage.OnTrainLeft();
    }
    else
    {
        brakeRun.OnTrainLeft();
    }
}

void Transfer::OnNextBlockFreed()
{
    LOG_INFO(F("Transfer NextBlockFreed"));
    if (this->exitStorage.IsSet())
    {
        storage.OnNextBlockFreed();
    }
    else
    {
        brakeRun.OnNextBlockFreed();
    }
}

void Transfer::SetNextBlock(IBlock* block)
{
    storage.SetNextBlock(block);
    brakeRun.SetNextBlock(block);
}

void Transfer::SwitchChanged()
{
    if (this->exitStorage.IsSet())
    {
        if (storage.IsNextFree())
        {
            storage.OnNextBlockFreed();
        }
    }
    else
    {
        if (brakeRun.IsNextFree())
        {
            brakeRun.OnNextBlockFreed();
        }
    }

    if (this->enterStorage.IsSet())
    {
        if (storage.IsFree())
        {
            lift.OnNextBlockFreed();
        }
    }
    else
    {
        if (brakeRun.IsFree())
        {
            lift.OnNextBlockFreed();
        }
    }
}

bool Transfer::IsFree()
{
    if (this->enterStorage.IsSet())
    {
        return storage.IsFree();
    }
    else
    {
        return brakeRun.IsFree();
    }
}

void Transfer::Restart()
{
    if (this->exitStorage.IsSet())
    {
        storage.Restart();
    }
    else
    {
        brakeRun.Restart();
    }
}

bool Transfer::IsExpectingorEntered()
{
    if (this->enterStorage.IsSet())
    {
        return storage.IsExpectingorEntered();
    }
    else
    {
        return brakeRun.IsExpectingorEntered();
    }
}

bool Transfer::EnterSwitchSafeToMove()
{
    return !IsExpectingorEntered();
}

bool Transfer::ExitSwitchSafeToMove()
{
    return !storage.IsLeaving() && !brakeRun.IsLeaving();
}

const int Transfer::CountTrains()
{
    int count = 0;
    if (storage.IsBlocked() || storage.IsExpectingorEntered())
    {
        count++;
    }
    if (brakeRun.IsBlocked() || brakeRun.IsExpectingorEntered())
    {
        count++;
    }
    return count;
}
