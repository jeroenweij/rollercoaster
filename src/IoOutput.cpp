/*************************************************************
* Created by J. Weij
*************************************************************/

#include "IoOutput.h"
#include "IoConfig.h"

using NodeLib::Message;
using NodeLib::Id;
using NodeLib::Operation;
using NodeLib::PinMode;

IoOutput::IoOutput(NodeLib::NodeMaster &node)
    : node(node)
{

}

void IoOutput::writeTwostate(const Id& id, bool value)
{
    LOG_INFO("writing node " << id.node << " channel " << id.channel << " Value:" << value);
    node.QueueMessage(id, value? 1:0);
}
