/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Logger.h"
#include "IoInput.h"


using NodeLib::Id;
using NodeLib::NodeMaster;

IoInput::IoInput(NodeMaster &nodeMaster)
    : logZone(Logger::get("Io input handler"))
{
    nodeMaster.RegisterHandler(*this);
}

void IoInput::ReceivedMessage(const NodeLib::Message &message)
{
    CallCallbacks(message.id, message.value);
}

void IoInput::CallCallbacks(const Id& id, const Value& value)
{
    auto range = this->callBackMap.equal_range(id);
    if (range.first != range.second)
    {
        LOG_DEBUG(this->logZone, "Recieving Call Callbacks");
        for (auto found = range.first; found != range.second; ++found)
        {
            (found->second)(value);
        }
        LOG_DEBUG(this->logZone, "Recieving done ");
    }
}

int IoInput::AddCallbackx(const Id& id, funct function)
{
    callBackMap.insert( std::make_pair(id, function));
    return 1;
}
