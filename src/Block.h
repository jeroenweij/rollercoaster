/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/id.h>

#include "Button.h"
#include "EStatus.h"
#include "IBlock.h"
#include "IoOutput.h"
#include <tools/Logger.h>

using NodeLib::Id;

class Block : public IBlock
{
  public:
    Block(IoOutput& outputHandler, const int approachId, const int blockId, const Id& deviceId, const int overridePin);
    ~Block() { }

    void Init();
    void Loop();

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
    const int approachPin;
    const int blockPin;
    const Id& deviceId;
    EStatus status;

  private:
    IBlock* nextBlock;
    Button overrideButton;
    bool override;
};
