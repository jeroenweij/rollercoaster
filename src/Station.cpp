/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Station.h"
#include "Arduino.h"
#include "IoConfig.h"
#include "pins.h"

Station::Station(IoInput& inputHandler, IoOutput& outputHandler) :
    Block(outputHandler, PIN_UI_STATION_APPR, PIN_UI_STATION_BLOCK, NodeId::stationBrake.id, PIN_MANUAL_STATION),
    dispatchOk(false),
    dispatchButton(PIN_DISPATCH, PIN_DISPATCH_LED),
    nextAction(-1)
{
    inputHandler.AddCallback(NodeId::stationEnter.id, this, &Station::OnTrainEnter, true);
    inputHandler.AddCallback(NodeId::stationSet.id, this, &Station::OnTrainSet, true);
    inputHandler.AddCallback(NodeId::liftEnter.id, this, &Station::OnTrainLeft, true);
    inputHandler.AddCallback(NodeId::liftLeft.id, this, &Station::OnNextBlockFreed, true);
}

void Station::OnTrainEnter()
{
    LOG_INFO(F("Station Train Enter"));
    Block::OnTrainEnter();
    nextAction = millis() + 2000;
}

void Station::OnTrainSet()
{
    LOG_INFO(F("Station Train Set"));
    Block::OnTrainSet();
    if (IsNextFree())
    {
        dispatchOk = true;
        dispatchButton.SetLed(true);
    }
    Hold();
}

void Station::OnTrainLeft()
{
    LOG_INFO(F("Station Train Left"));
    Block::OnTrainLeft();
    Hold();
}

void Station::OnNextBlockFreed()
{
    LOG_INFO(F("Station NextBlockFreed"));
    if (IsBlocked())
    {
        dispatchOk = true;
        dispatchButton.SetLed(true);
    }
}

void Station::Init()
{
    Block::Init();
    dispatchButton.Init();
}

void Station::Loop()
{
    Block::Loop();
    if (dispatchButton.IsPressed() && dispatchOk)
    {
        Release();
        dispatchButton.SetLed(false);
        dispatchOk = false;
    }

    if (millis() > nextAction)
    {
        LOG_INFO(F("Station Action"));
        if (status == EStatus::EXPECTING)
        {
            Release();
        }
        nextAction = -1;
    }
}
