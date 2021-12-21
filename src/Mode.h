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

    void AddResetCallback(IBlock* block);

  private:
    void ResetRestart();

    static EMode mode;

    IBlock* blocks[5];
    int     numBlocks;
};
