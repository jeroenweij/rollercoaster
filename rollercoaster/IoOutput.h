/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/NodeMaster.h>
#include <NodeLib/id.h>
#include "Logger.h"

using NodeLib::Id;

class IoOutput
{
public:
    IoOutput(NodeLib::NodeMaster& node);
    ~IoOutput(){ }

    void disableAllOutputs();
    void writeTwostate(const Id& id, bool value);

private:
    NodeLib::NodeMaster& node;
    Logger& logZone;
};
