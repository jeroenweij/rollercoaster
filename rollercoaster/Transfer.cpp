/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Transfer.h"
#include "NodeIds.h"

Transfer::Transfer(IoInput& inputHandler, IoOutput& outputHandler)
    : Block(outputHandler, RID::transferAproached, RID::transferBlocked, RID::transferBrake, Logger::get("TransferBlock"))
    , enterStorage(false)
    , exitStorage(false)
    , storage(outputHandler)
{
    inputHandler.AddCallback(RID::liftLeft, this, &Transfer::OnTrainApproaching, true);
    inputHandler.AddCallback(RID::transfertEnter, this, &Transfer::OnTrainEnter, true);
    inputHandler.AddCallback(RID::transfertSet, this, &Transfer::OnTrainSet, true);
    inputHandler.AddCallback(RID::stationSet, this, &Transfer::OnTrainLeft, true);
    inputHandler.AddCallback(RID::liftEnter, this, &Transfer::OnNextBlockFreed, true);

    inputHandler.AddCallback(RID::storageSet, this, &Transfer::OnStorageTrainSet, true);

    // setting switches
    inputHandler.AddCallback(RID::enterSwitch, this, &Transfer::OnEnterSwitchChanged);
    inputHandler.AddCallback(RID::exitSwitch, this, &Transfer::OnExitSwitchChanged);

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
        LOG_INFO(this->logZone, "SetEnterSwitch " << value);
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
        LOG_INFO(this->logZone, "SetExitSwitch " << value);
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
    LOG_INFO(this->logZone, "OnTrainApproaching");
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
    LOG_INFO(this->logZone, "OnTrainEnter");
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
    LOG_INFO(this->logZone, "OnTrainSet");
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
    LOG_INFO(this->logZone, "OnTrainLeft");
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
    LOG_INFO(this->logZone, "OnNextBlockFreed");
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
    outputHandler.writeTwostate(RID::transferInSwitch, this->enterStorage);
    outputHandler.writeTwostate(RID::transferOutSwitch, this->exitStorage);
}

void Transfer::Release()
{
    if (!exitStorage)
    {
        Block::Release();
    }
    else
    {
        LOG_ERROR(this->logZone, "releasing while switch is set");
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
