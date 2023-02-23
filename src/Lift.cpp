/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Lift.h"
#include "IoConfig.h"
#include "pins.h"

#define LIFTMAXTIMESECONDS 30

Lift::Lift(IoInput& inputHandler, IoOutput& outputHandler) :
    Block(outputHandler, PIN_UI_LIFT_APPR, PIN_UI_LIFT_BLOCK, NodeId::liftMotor.id, PIN_MANUAL_LIFT, LIFTMAXTIMESECONDS)
{
    inputHandler.AddCallback(NodeId::liftEnter.id, this, &Lift::OnTrainEnter, true);
    inputHandler.AddCallback(NodeId::liftSet.id, this, &Lift::OnTrainSet, true);
    inputHandler.AddCallback(NodeId::liftLeft.id, this, &Lift::OnTrainLeft, true);
    inputHandler.AddCallback(NodeId::stationSet.id, this, &Lift::OnNextBlockFreed, true);
}

void Lift::OnTrainEnter()
{
    LOG_INFO(F("Lift Train Enter"));
    Block::OnTrainEnter();
    Release();
}

void Lift::OnTrainSet()
{
    LOG_INFO(F("Lift Train Set"));
    if (IsExpectingorEntered() || IsFree())
    {
        Block::OnTrainSet();
        if (IsNextFree())
        {
            Release();
            nextBlock->OnTrainApproaching();
        }
        else
        {
            Hold();
        }
    }
}

void Lift::OnTrainLeft()
{
    LOG_INFO(F("Lift Train Left"));
    Block::OnTrainLeft();
    Hold();
}

void Lift::OnNextBlockFreed()
{
    LOG_INFO(F("Lift NextBlockFreed"));
    if (IsBlocked())
    {
        Release();
        nextBlock->OnTrainApproaching();
    }
}
