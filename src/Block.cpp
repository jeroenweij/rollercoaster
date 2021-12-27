/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Block.h"
#include "Arduino.h"
#include "Mode.h"

Block::Block(IoOutput&          outputHandler,
             const int          approachId,
             const int          blockId,
             const NodeLib::Id& deviceId,
             const int          overridePin,
             const int          maxReleaseTimeSeconds) :
    outputHandler(outputHandler),
    approachPin(approachId),
    blockPin(blockId),
    deviceId(deviceId),
    status(EStatus::FREE),
    nextBlock(nullptr),
    overrideButton(overridePin),
    manualOverride(false),
    released(false),
    maxReleaseTimeSeconds(maxReleaseTimeSeconds),
    releaseTime()
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
    switch (Mode::GetMode())
    {
        case EMode::OFF:
        case EMode::STOP:
            manualOverride = false;
            if (released)
            {
                Hold();
            }
            break;
        case EMode::MANUAL:
            if (overrideButton.IsPressed())
            {
                if (!manualOverride)
                {
                    LOG_INFO(F("Enable manual"));
                    manualOverride = true;
                    Release();
                }
            }
            else
            {
                if (manualOverride)
                {
                    LOG_INFO(F("Disable manual"));
                    manualOverride = false;
                    Hold();
                }
            }
            break;
        case EMode::AUTO:
            manualOverride = false;
            if (released && releaseTime.Finished())
            {
                Hold();
                Mode::Error();
            }
            break;
    }
}

void Block::OnTrainApproaching()
{
    SetStatus(EStatus::EXPECTING);
}

void Block::OnTrainEnter()
{
    SetStatus(EStatus::ENTERED);
}

void Block::OnTrainSet()
{
    if (IsApproaching() || IsFree())
    {
        SetStatus(EStatus::BLOCKED);
    }
}

void Block::OnTrainLeft()
{
    if (IsLeaving())
    {
        SetStatus(EStatus::FREE);
    }
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
        LOG_INFO("Set block Status to " << newStatus);
        this->status = newStatus;
        digitalWrite(approachPin, status == EStatus::ENTERED || status == EStatus::EXPECTING || status == EStatus::LEAVING);
        digitalWrite(blockPin, status == EStatus::BLOCKED || status == EStatus::LEAVING);
    }
}

void Block::Release()
{
    LOG_INFO("Release block");
    if ((Mode::IsAuto() || manualOverride))
    {
        outputHandler.writeTwostate(this->deviceId, true);
        released = true;
        releaseTime.Start(maxReleaseTimeSeconds * 1000);
        if (status == EStatus::BLOCKED)
        {
            SetStatus(EStatus::LEAVING);
        }
    }
}

void Block::Hold()
{
    outputHandler.writeTwostate(this->deviceId, false);
    released = false;
    releaseTime.Stop();
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

const bool Block::IsEntered() const
{
    return status == EStatus::ENTERED;
}

void Block::ResetStop()
{
    if ((status == EStatus::ENTERED) || (status == EStatus::LEAVING) || (status == EStatus::BLOCKED && IsNextFree()))
    {
        Release();
    }
}
