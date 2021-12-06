/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/id.h>

#include "IBlock.h"
#include "EStatus.h"
#include "IoOutput.h"
#include <tools/Logger.h>

using NodeLib::Id;

class Block : public IBlock
{
  public:
    Block(IoOutput& outputHandler, const Id& approachId, const Id& blockId, const Id& deviceId);
    ~Block() { }

    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();

    virtual void OnNextBlockFreed() = 0;

    void SetNextBlock(IBlock* block);
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

    IBlock* nextBlock;
};
