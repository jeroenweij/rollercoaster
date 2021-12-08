/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Rollercoaster.h"

#include "IoConfig.h"

using NodeLib::NodeMaster;

// Constructor
Rollercoaster::Rollercoaster(NodeMaster& nodeMaster)
    : inputHandler(nodeMaster)
    , outputHandler(nodeMaster)
    , station(inputHandler, outputHandler)
    , lift(inputHandler, outputHandler)
    , transfer(inputHandler, outputHandler, lift)
{
    station.SetNextBlock(&lift);
    lift.SetNextBlock(&transfer);
    transfer.SetNextBlock(&station);
}

void Rollercoaster::Init()
{
    transfer.Init();
}

void Rollercoaster::Loop()
{
    transfer.Loop();
}
