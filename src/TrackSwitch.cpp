/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Transfer.h"
#include "TrackSwitch.h"

TrackSwitch::TrackSwitch(IoInput& inputHandler, IoOutput& outputHandler, const NodeLib::Id& inputId, const NodeLib::Id& outputId, const Value valueWhenSet, const Value valueWhenUnset, Transfer& parent, bool (Transfer::*func)()) :
    outputHandler(outputHandler),
    outputId(outputId),
    valueWhenSet(valueWhenSet),
    valueWhenUnset(valueWhenUnset),
    set(false),
    parent(parent),
    SafeToMove(func)
{
    inputHandler.AddCallback(inputId, this, &TrackSwitch::Set);
}

void TrackSwitch::Set(const Value& value)
{
    const bool setTo = value > 0;
    if (setTo != set)
    {
        if ((parent.*SafeToMove)())
        {
            set = setTo;
            WriteOutput();
            parent.SwitchChanged();
        }
    }
}

bool TrackSwitch::IsSet() const
{
    return set;
}

void TrackSwitch::WriteOutput()
{
    const Value value = set ? valueWhenSet : valueWhenUnset;
    outputHandler.WriteValue(outputId, value);
}
