/*************************************************************
* Created by J. Weij
*************************************************************/

#include "StorageTrack.h"
#include "NodeIds.h"

StorageTrack::StorageTrack(IoOutput& outputHandler)
    : Block(outputHandler, RID::storageAproached, RID::storageBlocked, RID::storageBrake, Logger::get("StorageTrackBlock"))
{
    Hold();
}


void StorageTrack::OnTrainApproaching()
{
    LOG_INFO(this->logZone, "OnTrainApproaching");
    Block::OnTrainEnter();
}

void StorageTrack::OnTrainEnter()
{
    LOG_INFO(this->logZone, "OnTrainEnter");
    Release();
}

void StorageTrack::OnTrainSet(bool exitStorage, bool nextFree)
{
    LOG_INFO(this->logZone, "OnTrainSet");
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
    LOG_INFO(this->logZone, "OnTrainLeft");
    Block::OnTrainLeft();
    Hold();
}

void StorageTrack::OnNextBlockFreed()
{
    LOG_INFO(this->logZone, "OnNextBlockFreed");
    if (IsBlocked())
    {
        Release();
    }
}
