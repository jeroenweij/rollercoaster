/*************************************************************
 * Created by J. Weij
 *************************************************************/

#include "Station.h"
#include "Arduino.h"
#include "IoConfig.h"
#include "Mode.h"
#include "pins.h"

Station::Station(IoInput& inputHandler, IoOutput& outputHandler) :
    Block(outputHandler, PIN_UI_STATION_APPR, PIN_UI_STATION_BLOCK, NodeId::stationBrake.id, PIN_MANUAL_STATION),
    dispatchButton(PIN_DISPATCH, PIN_DISPATCH_LED),
    delayRelease(),
    gates(outputHandler)
{
    inputHandler.AddCallback(NodeId::stationEnter.id, this, &Station::OnTrainEnter, true);
    inputHandler.AddCallback(NodeId::stationHalfway.id, this, &Station::OnTrainHalfway, true);
    inputHandler.AddCallback(NodeId::stationSet.id, this, &Station::OnTrainSet, true);
    inputHandler.AddCallback(NodeId::liftEnter.id, this, &Station::OnTrainLeft, true);
    inputHandler.AddCallback(NodeId::liftLeft.id, this, &Station::OnNextBlockFreed, true);
}

void Station::OnTrainEnter()
{
    LOG_INFO(F("Station Train Enter"));
    Block::OnTrainEnter();
    delayRelease.Start(2000);
}

void Station::OnTrainHalfway()
{
    if (IsEntered() && IsReleased())
    {
        delayRelease.Start(800);
        Hold();
    }
}

void Station::OnTrainSet()
{
    if (IsExpectingorEntered() || IsFree())
    {
        LOG_INFO(F("Station Train Set"));
        delayRelease.Stop();
        Block::OnTrainSet();
        Hold();
    }
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
}

void Station::Restart()
{
    LOG_INFO(F("Station Stop Reset"));
    if (IsLeaving() || IsEntered())
    {
        Block::Restart();
    }
}

void Station::Init()
{
    Block::Init();
    dispatchButton.Init();
    gates.Init();
}

void Station::Loop()
{
    Block::Loop();
    const bool canDispatch = IsBlocked() && IsNextFree() && !gates.IsOpen() && Mode::IsAuto();

    dispatchButton.SetLed(canDispatch);

    if (canDispatch && dispatchButton.IsPressed())
    {
        Release();
    }

    if (delayRelease.Finished())
    {
        if (IsEntered())
        {
            Release();
        }
    }

    gates.Check(IsBlocked() && Mode::IsOn());
}
