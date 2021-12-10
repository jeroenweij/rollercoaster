/*************************************************************
* Created by J. Weij
*************************************************************/

#include "TrackSwitch.h"
#include "Arduino.h"
#include "Transfer.h"

TrackSwitch::TrackSwitch(IoOutput& outputHandler, const int inputPin, const int uiPin, const NodeLib::Id& outputId, const Value valueWhenSet, const Value valueWhenUnset, Transfer& parent, bool (Transfer::*func)()) :
    inputPin(inputPin),
    uiPin(uiPin),
    nextUpdate(0),
    outputHandler(outputHandler),
    outputId(outputId),
    valueWhenSet(valueWhenSet),
    valueWhenUnset(valueWhenUnset),
    set(false),
    parent(parent),
    SafeToMove(func)
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
}

void TrackSwitch::Loop()
{
    if (millis() > nextUpdate)
    {
        const bool setTo = !digitalRead(inputPin);
        if (setTo != set)
        {
            Set(setTo);
        }
        nextUpdate = millis() + 100;
    }
}

void TrackSwitch::Set(const bool setTo)
{
    LOG_INFO("Setting Switch " << (setTo ? "ON" : "OFF"));
    if ((parent.*SafeToMove)())
    {
        set = setTo;
        WriteOutput();
        digitalWrite(uiPin, set);
        parent.SwitchChanged();
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
