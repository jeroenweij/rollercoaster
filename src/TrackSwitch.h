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
    TrackSwitch(IoOutput& outputHandler, const int inputPin, const NodeLib::Id& outputId, const Value valueWhenSet, const Value valueWhenUnset, Transfer &parent, bool (Transfer::*func)());

    void Init();
    void Loop();
    bool IsSet() const;

  private:
    void Set(const bool setTo);
    void WriteOutput();

    const int inputPin;
    unsigned long nextUpdate;
    IoOutput& outputHandler;
    const NodeLib::Id& outputId;
    const Value valueWhenSet;
    const Value valueWhenUnset;
    bool set;
    Transfer& parent;
    bool (Transfer::*SafeToMove)();
};
