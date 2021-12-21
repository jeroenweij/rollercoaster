/*************************************************************
* Created by J. Weij
*************************************************************/

#include "IoOutput.h"
#include "IoConfig.h"

using NodeLib::Id;
using NodeLib::Message;
using NodeLib::Operation;
using NodeLib::PinMode;

IoOutput::IoOutput(NodeLib::NodeMaster& node) :
    node(node)
{
}

void IoOutput::writeTwostate(const Id& id, bool value)
{
    WriteValue(id, value ? 1 : 0);
}

void IoOutput::WriteValue(const NodeLib::Id& id, Value value)
{
    LOG_INFO("writing node " << id.node << " channel " << id.channel << " Value:" << value);
    node.QueueMessage(id, value);
}
