/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Block.h"
#include "Arduino.h"
#include "Mode.h"

Block::Block(IoOutput& outputHandler, const int approachId, const int blockId, const NodeLib::Id& deviceId, const int overridePin) :
    outputHandler(outputHandler),
    approachPin(approachId),
    blockPin(blockId),
    deviceId(deviceId),
    status(EStatus::FREE),
    nextBlock(nullptr),
    overrideButton(overridePin),
    override(false),
    eStop(false)
{
    pinMode(approachPin, OUTPUT);
    pinMode(blockPin, OUTPUT);
    digitalWrite(approachPin, HIGH);
    digitalWrite(blockPin, HIGH);
}

void Block::Init()
{
    pinMode(approachPin, OUTPUT);
    pinMode(blockPin, OUTPUT);
    digitalWrite(approachPin, LOW);
    digitalWrite(blockPin, LOW);

    overrideButton.Init();
}

void Block::Loop()
{
    if (Mode::IsStop() && !eStop)
    {
        Hold();
        eStop = true;
    }

    if (Mode::IsManual() && overrideButton.IsPressed())
    {
        if (!override)
        {
            Release();
            override = true;
        }
    }
    else
    {
        if (override)
        {
            Hold();
            override = false;
        }
    }
}

void Block::OnTrainAproaching()
{
    SetStatus(EStatus::EXPECTING);
}

void Block::OnTrainEnter()
{
    SetStatus(EStatus::ENTERED);
}

void Block::OnTrainSet()
{
    SetStatus(EStatus::BLOCKED);
}

void Block::OnTrainLeft()
{
    SetStatus(EStatus::FREE);
}

void Block::SetNextBlock(IBlock* block)
{
    this->nextBlock = block;
}

bool Block::IsNextFree()
{
    if (this->nextBlock == nullptr)
    {
        LOG_ERROR("nextblock is not set");
        return false;
    }
    return this->nextBlock->IsFree();
}

void Block::SetStatus(EStatus newStatus)
{
    if (this->status != newStatus)
    {
        LOG_INFO("Set Status to " << newStatus);
        this->status = newStatus;
        digitalWrite(approachPin, status == EStatus::ENTERED || status == EStatus::EXPECTING || status == EStatus::LEAVING);
        digitalWrite(blockPin, status == EStatus::BLOCKED || status == EStatus::LEAVING);
    }
}

void Block::Release()
{
    if (Mode::IsAuto() && !eStop)
    {
        outputHandler.writeTwostate(this->deviceId, true);
        if (status == EStatus::BLOCKED)
        {
            SetStatus(EStatus::LEAVING);
        }
    }
}

void Block::Hold()
{
    outputHandler.writeTwostate(this->deviceId, false);
}

bool Block::IsFree()
{
    return this->status == EStatus::FREE;
}
bool Block::IsBlocked()
{
    return this->status == EStatus::BLOCKED;
}
bool Block::IsLeaving()
{
    return this->status == EStatus::LEAVING;
}
bool Block::IsApproaching()
{
    return this->status == EStatus::EXPECTING || status == EStatus::ENTERED;
}

void Block::ResetStop()
{
    eStop = false;
    if ((status == EStatus::ENTERED) || (status == EStatus::LEAVING) || (status == EStatus::BLOCKED && IsNextFree()))
    {
        Release();
    }
}
