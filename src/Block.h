/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/id.h>
#include <tools/DelayTimer.h>
#include <tools/Logger.h>

#include "Button.h"
#include "EStatus.h"
#include "IBlock.h"
#include "IoOutput.h"

using NodeLib::Id;

class Block : public IBlock
{
  public:
    Block(IoOutput& outputHandler,
          const int approachId,
          const int blockId,
          const Id& deviceId,
          const int overridePin,
          const int maxReleaseTimeSeconds = 5);
    ~Block() {}

    void Init();
    void Loop();

    // IBlock implementation
    bool IsFree() override;
    void ResetStop() override;
    void OnTrainApproaching() override;
    void Clear() override;

    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();

    virtual void OnNextBlockFreed() = 0;

    void         SetNextBlock(IBlock* block);
    virtual bool IsNextFree();
    bool         IsBlocked();
    bool         IsLeaving();
    virtual bool IsApproaching();
    const bool   IsEntered() const;

  protected:
    void SetStatus(EStatus newStatus);
    void Release();
    void Hold();

    IoOutput& outputHandler;
    const int approachPin;
    const int blockPin;
    const Id& deviceId;
    IBlock*   nextBlock;

  private:
    EStatus    status;
    Button     overrideButton;
    bool       manualOverride;
    bool       released;
    const int  maxReleaseTimeSeconds;
    DelayTimer releaseTime;
};
