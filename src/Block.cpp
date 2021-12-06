/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Block.h"

Block::Block(IoOutput& outputHandler, const Id& approachId, const Id& blockId, const NodeLib::Id& deviceId)
    : outputHandler(outputHandler)
    , approachId(approachId)
    , blockId(blockId)
    , deviceId(deviceId)
    , status(EStatus::FREE)
{

}

void Block::OnTrainEnter()
{
    SetStatus(EStatus::EXPECTING);
}

void Block::OnTrainSet()
{
    SetStatus (EStatus::BLOCKED);
}

void Block::OnTrainLeft()
{
    SetStatus (EStatus::FREE);
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
        outputHandler.writeTwostate(this->approachId, status == EStatus::EXPECTING || status == EStatus::LEAVING);
        outputHandler.writeTwostate(this->blockId, status == EStatus::BLOCKED || status == EStatus::LEAVING);
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
