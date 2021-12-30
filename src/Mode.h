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
    static const bool  Error();

    void AddResetCallback(IBlock* block);

  private:
    void       ResetRestart();
    const bool EStopPressed();

    static EMode mode;

    IBlock* blocks[5];
    int     numBlocks;
};
