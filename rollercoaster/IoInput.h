/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/IVariableHandler.h>
#include <NodeLib/NodeMaster.h>
#include <functional>
#include <map>

#include "Logger.h"

using Value = uint8_t;
class IoInput : NodeLib::IVariableHandler
{
    typedef std::function<void(const Value&)> funct;

public:
    IoInput(NodeLib::NodeMaster& nodeMaster);
    ~IoInput() {}

    template <typename T>
    int AddCallback(const NodeLib::Id& id, T *inst, void (T::*func)(const Value&)) {
        return AddCallbackx(id, [=](const Value& value) {
            (inst->*func)(value);
        });
    }

    template <typename T>
    int AddCallback(const NodeLib::Id& id, T *inst, void (T::*func)(), bool boolValue) {
        return AddCallbackx(id, [=](const Value& value) {
            if (boolValue && value > 0)
            {
                (inst->*func)();
            }
        });
    }

private:
    int AddCallbackx(const NodeLib::Id& id, funct function);
    void CallCallbacks(const NodeLib::Id& id, const Value& value);

    //--- IVariableHandler interface implementation ---
    virtual void ReceivedMessage(const NodeLib::Message& message) ;

    std::multimap<const NodeLib::Id, funct> callBackMap;

    Logger& logZone;
};
