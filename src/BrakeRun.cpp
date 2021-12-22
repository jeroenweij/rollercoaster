/*************************************************************
* Created by J. Weij
*************************************************************/

#include "BrakeRun.h"
#include "Arduino.h"
#include "IoConfig.h"

BrakeRun::BrakeRun(IoOutput& outputHandler, IoInput& inputHandler, BrakeRunIds& nodeIds, const TrackSwitch& exitSwitch, const bool isStorage) :
    Block(outputHandler, nodeIds.approachLed, nodeIds.blockedLed, nodeIds.blockDevice, nodeIds.overridePin),
    exitSwitch(exitSwitch),
    isStorage(isStorage),
    nextAction(-1)
{
    inputHandler.AddCallback(nodeIds.onTrainEnter, this, &BrakeRun::OnTrainEnter, true);
    inputHandler.AddCallback(nodeIds.onTrainSet, this, &BrakeRun::OnTrainSet, true);
}

void BrakeRun::Loop()
{
    Block::Loop();
    if (millis() > nextAction)
    {
        LOG_INFO(F("Brakerun Action"));
        if (status == EStatus::ENTERED)
        {
            Release();
        }
        nextAction = -1;
    }
}

void BrakeRun::OnTrainApproaching()
{
    LOG_INFO(F("Brakerun Train Approaching"));
    Block::OnTrainApproaching();
}

void BrakeRun::OnTrainEnter()
{
    LOG_INFO(F("Brakerun Train Enter"));
    Block::OnTrainEnter();
    nextAction = millis() + 2000;
}

void BrakeRun::OnTrainSet()
{
    LOG_INFO(F("Brakerun Train Set"));
    Block::OnTrainSet();
    if (IsNextFree())
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
    LOG_INFO(F("Brakerun Train Left"));
    Block::OnTrainLeft();
    Hold();
}

void BrakeRun::OnNextBlockFreed()
{
    LOG_INFO(F("Brakerun NextBlockFreed"));
    if (IsBlocked())
    {
        Release();
    }
}

bool BrakeRun::IsNextFree()
{
    return ((exitSwitch.IsSet() == isStorage) && Block::IsNextFree());
}
