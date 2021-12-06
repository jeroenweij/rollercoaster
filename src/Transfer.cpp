/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Transfer.h"
#include "IoConfig.h"

BrakeRunIds brakeRunIds = {
    .approachLed = NodeId::transferAproached.id,
    .blockedLed = NodeId::transferBlocked.id,
    .blockDevice = NodeId::transferBrake.id,
    .onTrainEnter = NodeId::transfertEnter.id,
    .onTrainSet = NodeId::transfertSet.id
};

BrakeRunIds storageTrackIds = {
    .approachLed = NodeId::storageAproached.id,
    .blockedLed = NodeId::storageBlocked.id,
    .blockDevice = NodeId::storageBrake.id,
    .onTrainEnter = NodeId::transfertEnter.id,
    .onTrainSet = NodeId::storageSet.id
};

Transfer::Transfer(IoInput& inputHandler, IoOutput& outputHandler, Lift &lift) :
    enterStorage(inputHandler, outputHandler, NodeId::enterSwitch.id, NodeId::transferInSwitch.id, 0, 180, *this, &Transfer::EnterSwitchSafeToMove),
    exitStorage(inputHandler, outputHandler, NodeId::exitSwitch.id, NodeId::transferOutSwitch.id, 0, 180, *this, &Transfer::ExitSwitchSafeToMove),
    brakeRun(outputHandler, inputHandler, brakeRunIds, exitStorage, false),
    storage(outputHandler, inputHandler, brakeRunIds, exitStorage, true),
    lift(lift)
{
    inputHandler.AddCallback(NodeId::liftLeft.id, this, &Transfer::OnTrainApproaching, true);
    inputHandler.AddCallback(NodeId::stationSet.id, this, &Transfer::OnTrainLeft, true);
    inputHandler.AddCallback(NodeId::liftEnter.id, this, &Transfer::OnNextBlockFreed, true);
}

void Transfer::OnTrainApproaching()
{
    LOG_INFO("OnTrainApproaching");
    if (enterStorage.IsSet())
    {
        storage.OnTrainApproaching();
    }
    else
    {
        brakeRun.OnTrainApproaching();
    }
}

void Transfer::OnTrainLeft()
{
    LOG_INFO("OnTrainLeft");
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
    LOG_INFO("OnNextBlockFreed");
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
       if (storage.IsNextFree()){
           storage.OnNextBlockFreed();
       }
    }
    else
    {
        if (brakeRun.IsNextFree()){
            brakeRun.OnNextBlockFreed();
        }
    }

    if (this->enterStorage.IsSet())
    {
        if (storage.IsFree()){
            lift.OnNextBlockFreed();
        }
    }
    else
    {
        if (brakeRun.IsFree()){
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

bool Transfer::IsApproaching()
{
    if (this->enterStorage.IsSet())
    {
        return storage.IsApproaching();
    }
    else
    {
        return brakeRun.IsApproaching();
    }
}

bool Transfer::EnterSwitchSafeToMove()
{
    return !IsApproaching();
}

bool Transfer::ExitSwitchSafeToMove()
{
    return !storage.IsLeaving() && !brakeRun.IsLeaving();
}
