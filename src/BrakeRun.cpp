/*************************************************************
* Created by J. Weij
*************************************************************/

#include "BrakeRun.h"
#include "IoConfig.h"

BrakeRun::BrakeRun(IoOutput& outputHandler, IoInput inputHandler, BrakeRunIds& nodeIds, const TrackSwitch& exitSwitch, const bool isStorage) :
    Block(outputHandler, nodeIds.approachLed, nodeIds.blockedLed, nodeIds.blockDevice, nodeIds.overridePin),
    exitSwitch(exitSwitch),
    isStorage(isStorage)
{
    inputHandler.AddCallback(nodeIds.onTrainEnter, this, &BrakeRun::OnTrainEnter, true);
    inputHandler.AddCallback(nodeIds.onTrainSet, this, &BrakeRun::OnTrainSet, true);
}

void BrakeRun::OnTrainApproaching()
{
    LOG_INFO("OnTrainApproaching");
    Block::OnTrainEnter();
}

void BrakeRun::OnTrainEnter()
{
    LOG_INFO("OnTrainEnter");
    Release();
}

void BrakeRun::OnTrainSet()
{
    LOG_INFO("OnTrainSet");
    Block::OnTrainSet();
    if ((exitSwitch.IsSet() == isStorage) && IsNextFree())
    {
        Release();
    }
    else
    {
        Hold();
    }
}

void BrakeRun::OnTrainLeft()
{
    LOG_INFO("OnTrainLeft");
    Block::OnTrainLeft();
    Hold();
}

void BrakeRun::OnNextBlockFreed()
{
    LOG_INFO("OnNextBlockFreed");
    if (IsBlocked())
    {
        Release();
    }
}
