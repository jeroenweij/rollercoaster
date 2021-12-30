/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Rollercoaster.h"
#include "Arduino.h"
#include "IoConfig.h"
#include <pins.h>

using NodeLib::NodeMaster;

// Constructor
Rollercoaster::Rollercoaster(NodeMaster& nodeMaster) :
    inputHandler(nodeMaster),
    outputHandler(nodeMaster),
    mode(),
    station(inputHandler, outputHandler),
    lift(inputHandler, outputHandler),
    transfer(inputHandler, outputHandler, lift)
{
    station.SetNextBlock(&lift);
    lift.SetNextBlock(&transfer);
    transfer.SetNextBlock(&station);

    mode.AddResetCallback(&station);
    mode.AddResetCallback(&lift);
    mode.AddResetCallback(&transfer);

    pinMode(PIN_UI_PWM, OUTPUT);
    analogWrite(PIN_UI_PWM, 150);
}

void Rollercoaster::Init()
{
    mode.Init();
    transfer.Init();
    station.Init();
    lift.Init();
}

void Rollercoaster::Loop()
{
    mode.Loop();
    transfer.Loop();
    station.Loop();
    lift.Loop();

    if (Mode::IsOn() && CountTrains() > 2)
    {
        LOG_ERROR(F("Detected too many trains: ") << CountTrains());
        Mode::Error("Too many trains", true);
    }
}

const int Rollercoaster::CountTrains()
{
    int count = 0;
    if (station.IsBlocked() || station.IsApproaching())
    {
        count++;
    }
    if (lift.IsBlocked() || lift.IsApproaching())
    {
        count++;
    }
    return count + transfer.CountTrains();
}
