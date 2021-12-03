/*************************************************************
* Created by J. Weij
*************************************************************/

#include "IoOutput.h"
#include "NodeIds.h"

IoOutput::IoOutput(NodeLib::NodeMaster &node)
    : node(node)
{

}

void IoOutput::writeTwostate(const Id& id, bool value)
{
    LOG_INFO("writing node " << id.node << " channel " << id.channel << " Value:" << value);
    node.QueueMessage(id, value? 1:0);
}

void IoOutput::disableAllOutputs()
{
    writeTwostate(RID::stationBrake, false);
    writeTwostate(RID::stationAproached, false);
    writeTwostate(RID::stationBlocked, false);

    writeTwostate(RID::liftMotor, false);
    writeTwostate(RID::liftAproached, false);
    writeTwostate(RID::liftBlocked, false);

    writeTwostate(RID::transferBrake, false);
    writeTwostate(RID::transferBrake, false);
    writeTwostate(RID::transferInSwitch, false);
    writeTwostate(RID::transferOutSwitch, false);
    writeTwostate(RID::transferAproached, false);
    writeTwostate(RID::storageAproached, false);
    writeTwostate(RID::transferBlocked, false);
    writeTwostate(RID::storageBlocked, false);
}
