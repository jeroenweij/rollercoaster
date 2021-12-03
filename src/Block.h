/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/id.h>

#include "EStatus.h"
#include "IoOutput.h"
#include "Logger.h"

using NodeLib::Id;

class Block
{
  public:
    Block(IoOutput& outputHandler, const Id& approachId, const Id& blockId, const Id& deviceId);
    ~Block() { }

    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();

    virtual void OnNextBlockFreed() = 0;

    void SetNextBlock(Block* block);
    bool IsNextFree();
    virtual bool IsFree();
    bool IsBlocked();
    bool IsLeaving();
    virtual bool IsApproaching();

  protected:
    void SetStatus(EStatus newStatus);
    void Release();
    void Hold();

    IoOutput& outputHandler;
    const Id& approachId;
    const Id& blockId;
    const Id& deviceId;

  private:
    EStatus status;

    Block* nextBlock;
};
