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
    Block(IoOutput& outputHandler,
          const int approachId,
          const int blockId,
          const Id& deviceId,
          const int overridePin,
          const int maxReleaseTimeSeconds = 5);
    ~Block() {}

    void Init();
    void Loop();

    void OnTrainApproaching() override;
    void OnTrainEnter();
    void OnTrainLeft();
    void OnTrainSet();

    virtual void OnNextBlockFreed() = 0;

    void         SetNextBlock(IBlock* block);
    virtual bool IsNextFree();
    bool         IsFree() override;
    bool         IsBlocked();
    bool         IsLeaving();
    virtual bool IsApproaching();
    void         ResetStop() override;

  protected:
    void SetStatus(EStatus newStatus);
    void Release();
    void Hold();

    IoOutput& outputHandler;
    const int approachPin;
    const int blockPin;
    const Id& deviceId;
    EStatus   status;
    IBlock*   nextBlock;

  private:
    Button        overrideButton;
    bool          manualOverride;
    bool          released;
    const int     maxReleaseTimeSeconds;
    unsigned long releaseTime;
};
