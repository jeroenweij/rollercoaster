/*************************************************************
* Created by J. Weij
*************************************************************/

#include "IoConfig.h"
#include <NodeLib/id.h>

using NodeLib::Id;
using NodeLib::NodeMaster;
using NodeLib::Operation;
using NodeLib::PinMode;

IoConfig::IoConfig(NodeMaster& node) :
    node(node)
{
}

void IoConfig::ConfigureIo()
{
    ConfigureChannel(NodeId::stationEnter);
    ConfigureChannel(NodeId::stationSet);
    ConfigureChannel(NodeId::stationBrake);
    ConfigureChannel(NodeId::stationAproached);
    ConfigureChannel(NodeId::stationBlocked);
    ConfigureChannel(NodeId::liftEnter);
    ConfigureChannel(NodeId::liftSet);
    ConfigureChannel(NodeId::liftLeft);
    ConfigureChannel(NodeId::liftMotor);
    ConfigureChannel(NodeId::liftAproached);
    ConfigureChannel(NodeId::liftBlocked);
    ConfigureChannel(NodeId::transfertEnter);
    ConfigureChannel(NodeId::transfertSet);
    ConfigureChannel(NodeId::transferBrake);
    ConfigureChannel(NodeId::transferInSwitch);
    ConfigureChannel(NodeId::transferOutSwitch);
    ConfigureChannel(NodeId::transferAproached);
    ConfigureChannel(NodeId::transferBlocked);
    ConfigureChannel(NodeId::storageSet);
    ConfigureChannel(NodeId::storageBrake);
    ConfigureChannel(NodeId::storageAproached);
    ConfigureChannel(NodeId::storageBlocked);
    ConfigureChannel(NodeId::enterSwitch);
    ConfigureChannel(NodeId::exitSwitch);
}

void IoConfig::ConfigureChannel(const NodeId::IoChannel& channel)
{
    Id setId(channel.id.node, channel.id.channel, Operation::SETMODE);
    node.QueueMessage(setId, static_cast<Value>(channel.pinMode));

    if (channel.pinMode == PinMode::ANALOG_IN || channel.pinMode == PinMode::DIGITAL_IN)
    {
        setId.operation = Operation::GET;
    }
    else
    {
        setId.operation = Operation::SET;
    }
    node.QueueMessage(setId, 0);

    node.FlushNow();
}
