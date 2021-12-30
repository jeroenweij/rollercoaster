/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "EMode.h"
#include "IBlock.h"

class Mode
{
  public:
    Mode();

    void Init();
    void Loop();

    static const EMode GetMode();
    static const bool  IsManual();
    static const bool  IsAuto();
    static const bool  IsStop();
    static const bool  IsOn();
    static const bool  Error(const bool doClearOnReset = false);

    void AddResetCallback(IBlock* block);

  private:
    void       ResetRestart();
    const bool EStopPressed();

    static EMode mode;
    static bool  clearOnReset;

    IBlock* blocks[5];
    int     numBlocks;
};
