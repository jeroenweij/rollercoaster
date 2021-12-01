/*************************************************************
* Created by J. Weij
*************************************************************/

#include "IoOutput.h"
#include "NodeIds.h"

IoOutput::IoOutput(NodeLib::NodeMaster &node)
    : node(node)
    , logZone(Logger::get("Io output handler"))
{

}

void IoOutput::writeTwostate(const Id& id, bool value)
{
    LOG_INFO(this->logZone, "writing node " << id.node << " channel " << id.channel << " Value:" << value);
    node.WriteMessage(id, value? 1:0);
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
