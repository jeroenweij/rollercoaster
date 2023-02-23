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
    delayRelease()
{
    inputHandler.AddCallback(nodeIds.onTrainHalfway, this, &BrakeRun::OnTrainHalfway, true);
    inputHandler.AddCallback(nodeIds.onTrainEnter, this, &BrakeRun::OnTrainEnter, true);
    inputHandler.AddCallback(nodeIds.onTrainSet, this, &BrakeRun::OnTrainSet, true);
    inputHandler.AddCallback(nodeIds.onTrainCleared, this, &BrakeRun::OnTrainCleared, true);
}

void BrakeRun::Loop()
{
    Block::Loop();
    if (delayRelease.Finished())
    {
        LOG_INFO(F("Brakerun Action"));
        if (IsEntered())
        {
            Release();
        }
        else if (IsBlocked() && IsNextFree())
        {
            Release();
        }
    }
}

void BrakeRun::OnTrainHalfway()
{
    if (IsEntered() && IsReleased())
    {
        delayRelease.Start(800);
        Hold();
    }
}

void BrakeRun::OnTrainApproaching()
{
    LOG_INFO(F("Brakerun Train Approaching"));
    Block::OnTrainApproaching();
}

void BrakeRun::OnTrainEnter()
{
    if (IsExpecting())
    {
        LOG_INFO(F("Brakerun Train Enter "));
        Block::OnTrainEnter();

        delayRelease.Start(1000);
    }
}

void BrakeRun::OnTrainSet()
{
    LOG_INFO(F("Brakerun Train Set"));
    delayRelease.Stop();
    Block::OnTrainSet();

    Hold();
    delayRelease.Start(500);
}

void BrakeRun::OnTrainCleared()
{
    if (IsLeaving())
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
