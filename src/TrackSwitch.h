/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <tools/FunctionPtr.h>

#include "NodeLib/id.h"

#include "IoInput.h"
#include "IoOutput.h"

class Transfer;
class TrackSwitch
{
  public:
    TrackSwitch(IoInput& inputHandler, IoOutput& outputHandler, const NodeLib::Id& inputId, const NodeLib::Id& outputId, const Value valueWhenSet, const Value valueWhenUnset, Transfer &parent, bool (Transfer::*func)());

    void Set(const Value& value);
    bool IsSet();

  private:
    void WriteOutput();

    IoOutput& outputHandler;
    const NodeLib::Id& outputId;
    const Value valueWhenSet;
    const Value valueWhenUnset;
    bool set;
    Transfer& parent;
    bool (Transfer::*SafeToMove)();
};
