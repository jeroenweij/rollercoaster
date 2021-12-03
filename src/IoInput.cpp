/*************************************************************
* Created by J. Weij
*************************************************************/

#include <NodeLib/EPinMode.h>
#include <tools/Logger.h>

#include "IoInput.h"

using NodeLib::Id;
using NodeLib::NodeMaster;
using NodeLib::Operation;
using NodeLib::PinMode;

IoInput::IoInput(NodeMaster& nodeMaster) :
    numCallbacks(0)
{
    nodeMaster.RegisterHandler(this);
}

void IoInput::ReceivedMessage(const NodeLib::Message& message)
{
    CallCallbacks(message.id, message.value);
}

void IoInput::CallCallbacks(const Id& id, const Value& value)
{
    for (int i = 0; i < numCallbacks; i++)
    {
        if (callBackMap[i].id == id)
        {
            LOG_DEBUG("Calling Callback");
            callBackMap[i].callback(value);
        }
    }
}

int IoInput::AddCallbackx(const Id& id, funct function)
{
    if (numCallbacks < maxCallbacks)
    {
        callBackMap[numCallbacks].id = id;
        callBackMap[numCallbacks].callback = function;

        numCallbacks++;
    }
    else
    {
        LOG_ERROR("Callback table is full");
    }
    return 1;
}
