/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Station.h"
#include "NodeIds.h"

Station::Station(IoInput& inputHandler, IoOutput& outputHandler)
    : Block(outputHandler, RID::stationAproached, RID::stationBlocked, RID::stationBrake)
{
    inputHandler.AddCallback(RID::stationEnter, this, &Station::OnTrainEnter, true);
    inputHandler.AddCallback(RID::stationSet, this, &Station::OnTrainSet, true);
    inputHandler.AddCallback(RID::liftEnter, this, &Station::OnTrainLeft, true);
    inputHandler.AddCallback(RID::liftLeft, this, &Station::OnNextBlockFreed, true);

    Hold();
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
