/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Lift.h"
#include "NodeIds.h"

Lift::Lift(IoInput& inputHandler, IoOutput& outputHandler)
    : Block(outputHandler, RID::liftAproached, RID::liftBlocked, RID::liftMotor, Logger::get("LiftBlock"))
{
    inputHandler.AddCallback(RID::liftEnter, this, &Lift::OnTrainEnter, true);
    inputHandler.AddCallback(RID::liftSet, this, &Lift::OnTrainSet, true);
    inputHandler.AddCallback(RID::liftLeft, this, &Lift::OnTrainLeft, true);
    inputHandler.AddCallback(RID::stationSet, this, &Lift::OnNextBlockFreed, true);

    Hold();
}

void Lift::OnTrainEnter()
{
    LOG_INFO(this->logZone, "OnTrainEnter");
    Block::OnTrainEnter();
    Release();
}

void Lift::OnTrainSet()
{
    LOG_INFO(this->logZone, "OnTrainSet");
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

void Lift::OnTrainLeft()
{
    LOG_INFO(this->logZone, "OnTrainLeft");
    Block::OnTrainLeft();
    Hold();
}

void Lift::OnNextBlockFreed()
{
    LOG_INFO(this->logZone, "OnNextBlockFreed");
    if (IsBlocked()){
        Release();
    }
}