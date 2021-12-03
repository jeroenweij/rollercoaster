/*************************************************************
* Created by J. Weij
*************************************************************/

#include "StorageTrack.h"
#include "NodeIds.h"

StorageTrack::StorageTrack(IoOutput& outputHandler)
    : Block(outputHandler, RID::storageAproached, RID::storageBlocked, RID::storageBrake)
{
    Hold();
}


void StorageTrack::OnTrainApproaching()
{
    LOG_INFO("OnTrainApproaching");
    Block::OnTrainEnter();
}

void StorageTrack::OnTrainEnter()
{
    LOG_INFO("OnTrainEnter");
    Release();
}

void StorageTrack::OnTrainSet(bool exitStorage, bool nextFree)
{
    LOG_INFO("OnTrainSet");
    Block::OnTrainSet();
    if (exitStorage && nextFree)
    {
        Release();
    }
    else
    {
        Hold();
    }
}

void StorageTrack::OnTrainLeft()
{
    LOG_INFO("OnTrainLeft");
    Block::OnTrainLeft();
    Hold();
}

void StorageTrack::OnNextBlockFreed()
{
    LOG_INFO("OnNextBlockFreed");
    if (IsBlocked())
    {
        Release();
    }
}
