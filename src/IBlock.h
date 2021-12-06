/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/id.h>

#include "EStatus.h"
#include "IoOutput.h"
#include <tools/Logger.h>

using NodeLib::Id;

class IBlock
{
  public:

    virtual bool IsFree() = 0;
};
