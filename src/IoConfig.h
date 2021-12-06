/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once
#include <NodeLib/NodeMaster.h>
#include <NodeLib/id.h>
#include <NodeLib/EPinMode.h>

namespace NodeId
{
    using NodeLib::Id;
    using NodeLib::Operation;
    using NodeLib::PinMode;

    struct IoChannel
    {
        const Id id;
        const PinMode pinMode;

        IoChannel(const uint8_t node, const NodeLib::ChannelId channel, const Operation operation, const PinMode pinMode) :
            id(node, channel, operation),
            pinMode(pinMode)
        {
        }
    };

    // Station
    // In
    static const IoChannel stationEnter(1, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel stationSet(1, NodeLib::ChannelId::DIGITAL_2, Operation::VALUE, PinMode::DIGITAL_IN);
    // Out
    static const IoChannel stationBrake(1,  NodeLib::ChannelId::DIGITAL_3, Operation::SET, PinMode::DIGITAL_OUT);

    // UI Out
    static const IoChannel stationAproached(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel stationBlocked(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);

    // Lift
    // In
    static const IoChannel liftEnter(0, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel liftSet(0, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel liftLeft(0, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    // Out
    static const IoChannel liftMotor(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);

    // UI Out
    static const IoChannel liftAproached(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel liftBlocked(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);

    // Transfer
    // In
    static const IoChannel transfertEnter(0, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel transfertSet(0, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    // Out
    static const IoChannel transferBrake(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel transferInSwitch(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::SERVO);
    static const IoChannel transferOutSwitch(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::SERVO);

    // UI Out
    static const IoChannel transferAproached(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel transferBlocked(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);

    // Storage
    // In
    static const IoChannel storageSet(0, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);

    // Out
    static const IoChannel storageBrake(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);

    // UI Out
    static const IoChannel storageAproached(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel storageBlocked(0, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);

    // Switches
    // UI In
    static const IoChannel enterSwitch(0, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel exitSwitch(0, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
}

class IoConfig
{
  public:
    IoConfig(NodeLib::NodeMaster& node);
    void ConfigureIo();

  private:
    void ConfigureChannel(const NodeId::IoChannel& channel);

    NodeLib::NodeMaster& node;
};