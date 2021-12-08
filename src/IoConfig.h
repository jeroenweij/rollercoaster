/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once
#include <NodeLib/EPinMode.h>
#include <NodeLib/NodeMaster.h>
#include <NodeLib/id.h>

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
    static const IoChannel stationBrake(1, NodeLib::ChannelId::MOSFET_1, Operation::SET, PinMode::DIGITAL_OUT);

    // UI Out
    static const IoChannel stationAproached(7, NodeLib::ChannelId::DIGITAL_1, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel stationBlocked(7, NodeLib::ChannelId::DIGITAL_2, Operation::SET, PinMode::DIGITAL_OUT);

    // Lift
    // In
    static const IoChannel liftEnter(2, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel liftSet(4, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel liftLeft(5, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    // Out
    static const IoChannel liftMotor(3, NodeLib::ChannelId::MOSFET_1, Operation::SET, PinMode::DIGITAL_OUT);

    // UI Out
    static const IoChannel liftAproached(7, NodeLib::ChannelId::DIGITAL_3, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel liftBlocked(7, NodeLib::ChannelId::DIGITAL_4, Operation::SET, PinMode::DIGITAL_OUT);

    // Transfer
    // In
    static const IoChannel brakeRunEnter(5, NodeLib::ChannelId::DIGITAL_2, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel brakeRunSet(6, NodeLib::ChannelId::DIGITAL_1, Operation::VALUE, PinMode::DIGITAL_IN);
    // Out
    static const IoChannel brakerunBrake(6, NodeLib::ChannelId::MOSFET_1, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel transferInSwitch(5, NodeLib::ChannelId::SERVO_1, Operation::SET, PinMode::SERVO);
    static const IoChannel transferOutSwitch(6, NodeLib::ChannelId::SERVO_1, Operation::SET, PinMode::SERVO);

    // UI Out
    static const IoChannel brakerunAproached(7, NodeLib::ChannelId::DIGITAL_5, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel brakerunBlocked(7, NodeLib::ChannelId::DIGITAL_6, Operation::SET, PinMode::DIGITAL_OUT);

    // Storage
    // In
    static const IoChannel storageEnter(5, NodeLib::ChannelId::DIGITAL_3, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel storageSet(6, NodeLib::ChannelId::DIGITAL_2, Operation::VALUE, PinMode::DIGITAL_IN);

    // Out
    static const IoChannel storageBrake(6, NodeLib::ChannelId::MOSFET_2, Operation::SET, PinMode::DIGITAL_OUT);

    // UI Out
    static const IoChannel storageAproached(7, NodeLib::ChannelId::ANALOG_1, Operation::SET, PinMode::DIGITAL_OUT);
    static const IoChannel storageBlocked(7, NodeLib::ChannelId::ANALOG_2, Operation::SET, PinMode::DIGITAL_OUT);

    // Switches
    // UI In
    static const IoChannel enterSwitch(7, NodeLib::ChannelId::SERVO_1, Operation::VALUE, PinMode::DIGITAL_IN);
    static const IoChannel exitSwitch(7, NodeLib::ChannelId::SERVO_2, Operation::VALUE, PinMode::DIGITAL_IN);
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
