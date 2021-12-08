/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Station.h"
#include "IoConfig.h"

Station::Station(IoInput& inputHandler, IoOutput& outputHandler)
    : Block(outputHandler, NodeId::stationAproached.id, NodeId::stationBlocked.id, NodeId::stationBrake.id)
{
    inputHandler.AddCallback(NodeId::stationEnter.id, this, &Station::OnTrainEnter, true);
    inputHandler.AddCallback(NodeId::stationSet.id, this, &Station::OnTrainSet, true);
    inputHandler.AddCallback(NodeId::liftEnter.id, this, &Station::OnTrainLeft, true);
    inputHandler.AddCallback(NodeId::liftLeft.id, this, &Station::OnNextBlockFreed, true);
}

void Station::OnTrainEnter()
{
    LOG_INFO("OnTrainEnter");
    Block::OnTrainEnter();
    Release();
}

void Station::OnTrainSet()
{
    LOG_INFO("OnTrainSet");
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

void Station::OnTrainLeft()
{
    LOG_INFO("OnTrainLeft");
    Block::OnTrainLeft();
    Hold();
}

void Station::OnNextBlockFreed()
{
    LOG_INFO("OnNextBlockFreed");
    if (IsBlocked()){
        Release();
    }
}
