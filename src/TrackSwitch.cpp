/*************************************************************
* Created by J. Weij
*************************************************************/

#include "TrackSwitch.h"
#include "Arduino.h"
#include "Mode.h"
#include "Transfer.h"

TrackSwitch::TrackSwitch(IoOutput&          outputHandler,
                         const int          inputPin,
                         const int          uiPin,
                         const NodeLib::Id& outputId,
                         const Value        valueWhenSet,
                         const Value        valueWhenUnset,
                         Transfer&          parent,
                         bool (Transfer::*func)()) :
    inputPin(inputPin),
    uiPin(uiPin),
    nextUpdate(),
    outputHandler(outputHandler),
    outputId(outputId),
    valueWhenSet(valueWhenSet),
    valueWhenUnset(valueWhenUnset),
    set(false),
    parent(parent),
    SafeToMove(func),
    delayTimer()
{
    pinMode(inputPin, INPUT_PULLUP);
    pinMode(uiPin, OUTPUT);
    digitalWrite(uiPin, HIGH);
}

void TrackSwitch::Init()
{
    pinMode(inputPin, INPUT_PULLUP);
    pinMode(uiPin, OUTPUT);
    digitalWrite(uiPin, LOW);
    WriteOutput();
}

void TrackSwitch::Loop()
{
    if (Mode::IsOn() && (nextUpdate.Finished() || !nextUpdate.isRunning()))
    {
        const bool setTo = !digitalRead(inputPin);
        if (setTo != set)
        {
            Set(setTo);
        }
        nextUpdate.Start(100);
    }

    if (delayTimer.Finished())
    {
        parent.SwitchChanged();
    }
}

void TrackSwitch::Set(const bool setTo)
{
    if ((parent.*SafeToMove)())
    {
        LOG_INFO("Setting Switch " << (setTo ? "ON" : "OFF"));
        set = setTo;
        WriteOutput();
        digitalWrite(uiPin, set);
        delayTimer.Start(1000);
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
