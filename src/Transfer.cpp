/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Transfer.h"
#include "IoConfig.h"

Transfer::Transfer(IoInput& inputHandler, IoOutput& outputHandler)
    : Block(outputHandler, NodeId::transferAproached.id, NodeId::transferBlocked.id, NodeId::transferBrake.id)
    , enterStorage(false)
    , exitStorage(false)
    , storage(outputHandler)
{
    inputHandler.AddCallback(NodeId::liftLeft.id, this, &Transfer::OnTrainApproaching, true);
    inputHandler.AddCallback(NodeId::transfertEnter.id, this, &Transfer::OnTrainEnter, true);
    inputHandler.AddCallback(NodeId::transfertSet.id, this, &Transfer::OnTrainSet, true);
    inputHandler.AddCallback(NodeId::stationSet.id, this, &Transfer::OnTrainLeft, true);
    inputHandler.AddCallback(NodeId::liftEnter.id, this, &Transfer::OnNextBlockFreed, true);

    inputHandler.AddCallback(NodeId::storageSet.id, this, &Transfer::OnStorageTrainSet, true);

    // setting switches
    inputHandler.AddCallback(NodeId::enterSwitch.id, this, &Transfer::OnEnterSwitchChanged);
    inputHandler.AddCallback(NodeId::exitSwitch.id, this, &Transfer::OnExitSwitchChanged);

    Hold();
    SetSwitches();
}

void Transfer::OnEnterSwitchChanged(const Value& value)
{
    bool enableSwitch = value > 0;
    if (this->enterStorage != enableSwitch)
    {
        SetEnterSwitch(enableSwitch);
    }
}

void Transfer::OnExitSwitchChanged(const Value& value)
{
    bool enableSwitch = value > 0;
    if (this->exitStorage != enableSwitch)
    {
        SetExitSwitch(enableSwitch);
    }
}

bool Transfer::SetEnterSwitch(bool value)
{
    if (this->enterStorage != value)
    {
        LOG_INFO("SetEnterSwitch " << value);
        if (!IsApproaching())
        {
            this->enterStorage = value;
            SetSwitches();
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool Transfer::SetExitSwitch(bool value)
{
    if (this->exitStorage != value)
    {
        LOG_INFO("SetExitSwitch " << value);
        if (!storage.IsLeaving() && !IsLeaving())
        {
            this->exitStorage = value;
            SetSwitches();
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Transfer::OnStorageTrainSet()
{
    storage.OnTrainSet(this->exitStorage, IsNextFree());
}

void Transfer::OnTrainApproaching()
{
    LOG_INFO("OnTrainApproaching");
    if (enterStorage)
    {
        storage.OnTrainApproaching();
    }
    else
    {
        Block::OnTrainEnter();
    }
}

void Transfer::OnTrainEnter()
{
    LOG_INFO("OnTrainEnter");
    if (enterStorage)
    {
        storage.OnTrainEnter();
    }
    else
    {
        Release();
    }
}

void Transfer::OnTrainSet()
{
    LOG_INFO("OnTrainSet");
    Block::OnTrainSet();
    if (!this->exitStorage && IsNextFree())
    {
        Release();
    }
    else
    {
        Hold();
    }
}

void Transfer::OnTrainLeft()
{
    LOG_INFO("OnTrainLeft");
    if (this->exitStorage)
    {
        storage.OnTrainLeft();
    }
    else
    {
        Block::OnTrainLeft();
        Hold();
    }
}

void Transfer::OnNextBlockFreed()
{
    LOG_INFO("OnNextBlockFreed");
    if (this->exitStorage)
    {
        storage.OnNextBlockFreed();
    }
    else
    {
        if (IsBlocked()){
            Release();
        }
    }
}

void Transfer::SetSwitches()
{
    outputHandler.writeTwostate(NodeId::transferInSwitch.id, this->enterStorage);
    outputHandler.writeTwostate(NodeId::transferOutSwitch.id, this->exitStorage);
}

void Transfer::Release()
{
    if (!exitStorage)
    {
        Block::Release();
    }
    else
    {
        LOG_ERROR("releasing while switch is set");
    }
}

bool Transfer::IsFree()
{
    if (this->enterStorage)
    {
        return storage.IsFree();
    }
    else
    {
        return Block::IsFree();
    }
}

bool Transfer::IsApproaching()
{
    if (this->enterStorage)
    {
        return storage.IsApproaching();
    }
    else
    {
        return Block::IsApproaching();
    }
}
