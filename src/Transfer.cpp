/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Transfer.h"
#include "IoConfig.h"

Transfer::Transfer(IoInput& inputHandler, IoOutput& outputHandler) :
    Block(outputHandler, NodeId::transferAproached.id, NodeId::transferBlocked.id, NodeId::transferBrake.id),
    enterStorage(inputHandler,outputHandler, NodeId::enterSwitch.id, NodeId::transferInSwitch.id, 0, 180, *this, &Transfer::EnterSwitchSafeToMove),
    exitStorage(inputHandler,outputHandler, NodeId::exitSwitch.id, NodeId::transferOutSwitch.id, 0, 180, *this, &Transfer::ExitSwitchSafeToMove),
    storage(outputHandler)
{
    inputHandler.AddCallback(NodeId::liftLeft.id, this, &Transfer::OnTrainApproaching, true);
    inputHandler.AddCallback(NodeId::transfertEnter.id, this, &Transfer::OnTrainEnter, true);
    inputHandler.AddCallback(NodeId::transfertSet.id, this, &Transfer::OnTrainSet, true);
    inputHandler.AddCallback(NodeId::stationSet.id, this, &Transfer::OnTrainLeft, true);
    inputHandler.AddCallback(NodeId::liftEnter.id, this, &Transfer::OnNextBlockFreed, true);

    inputHandler.AddCallback(NodeId::storageSet.id, this, &Transfer::OnStorageTrainSet, true);

    Hold();
}

void Transfer::OnStorageTrainSet()
{
    storage.OnTrainSet(this->exitStorage.IsSet(), IsNextFree());
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
        Block::OnTrainEnter();
    }
}

void Transfer::OnTrainEnter()
{
    LOG_INFO("OnTrainEnter");
    if (enterStorage.IsSet())
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
    if (!this->exitStorage.IsSet() && IsNextFree())
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
    if (this->exitStorage.IsSet())
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
    if (this->exitStorage.IsSet())
    {
        storage.OnNextBlockFreed();
    }
    else
    {
        if (IsBlocked())
        {
            Release();
        }
    }
}

void Transfer::Release()
{
    if (!exitStorage.IsSet())
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
    if (this->enterStorage.IsSet())
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
    if (this->enterStorage.IsSet())
    {
        return storage.IsApproaching();
    }
    else
    {
        return Block::IsApproaching();
    }
}

bool Transfer::EnterSwitchSafeToMove()
{
    return !IsApproaching();
}

bool Transfer::ExitSwitchSafeToMove()
{
    return !storage.IsLeaving() && !IsLeaving();
}
