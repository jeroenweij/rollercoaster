/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Lift.h"
#include "IoConfig.h"
#include "pins.h"

Lift::Lift(IoInput& inputHandler, IoOutput& outputHandler)
    : Block(outputHandler, PIN_LIFT_APPR, PIN_LIFT_BLOCK, NodeId::liftMotor.id, PIN_MANUAL_LIFT)
{
    inputHandler.AddCallback(NodeId::liftEnter.id, this, &Lift::OnTrainEnter, true);
    inputHandler.AddCallback(NodeId::liftSet.id, this, &Lift::OnTrainSet, true);
    inputHandler.AddCallback(NodeId::liftLeft.id, this, &Lift::OnTrainLeft, true);
    inputHandler.AddCallback(NodeId::stationSet.id, this, &Lift::OnNextBlockFreed, true);
}

void Lift::OnTrainEnter()
{
    LOG_INFO("OnTrainEnter");
    Block::OnTrainEnter();
    Release();
}

void Lift::OnTrainSet()
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

void Lift::OnTrainLeft()
{
    LOG_INFO("OnTrainLeft");
    Block::OnTrainLeft();
    Hold();
}

void Lift::OnNextBlockFreed()
{
    LOG_INFO("OnNextBlockFreed");
    if (IsBlocked()){
        Release();
    }
}
