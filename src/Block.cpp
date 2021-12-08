/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Block.h"
#include "Arduino.h"

Block::Block(IoOutput& outputHandler, const int approachId, const int blockId, const NodeLib::Id& deviceId) :
    outputHandler(outputHandler), approachPin(approachId), blockPin(blockId), deviceId(deviceId), status(EStatus::FREE)
{
}

void Block::Init()
{
    pinMode(approachPin, OUTPUT);
    pinMode(blockPin, OUTPUT);
    digitalWrite(approachPin, LOW);
    digitalWrite(blockPin, LOW);
}

void Block::OnTrainEnter()
{
    SetStatus(EStatus::EXPECTING);
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
        digitalWrite(approachPin, status == EStatus::EXPECTING || status == EStatus::LEAVING);
        digitalWrite(blockPin, status == EStatus::BLOCKED || status == EStatus::LEAVING);
    }
}

void Block::Release()
{
    outputHandler.writeTwostate(this->deviceId, true);
    if (status == EStatus::BLOCKED)
    {
        SetStatus(EStatus::LEAVING);
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
    return this->status == EStatus::EXPECTING;
}
