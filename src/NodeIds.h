/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once
#include <NodeLib/id.h>

namespace RID
{
    using NodeLib::Id;

    // Station
    // In
    static const Id stationEnter(0, 0, Operation::GET);
    static const Id stationSet(0, 0, Operation::GET);
    // Out
    static const Id stationBrake(0, 0, Operation::SET);

    // UI Out
    static const Id stationAproached(0, 0, Operation::SET);
    static const Id stationBlocked(0, 0, Operation::SET);

    // Lift
    // In
    static const Id liftEnter(0, 0, Operation::GET);
    static const Id liftSet(0, 0, Operation::GET);
    static const Id liftLeft(0, 0, Operation::GET);
    // Out
    static const Id liftMotor(0, 0, Operation::SET);

    // UI Out
    static const Id liftAproached(0, 0, Operation::SET);
    static const Id liftBlocked(0, 0, Operation::SET);

    // Transfer
    // In
    static const Id transfertEnter(0, 0, Operation::GET);
    static const Id transfertSet(0, 0, Operation::GET);
    // Out
    static const Id transferBrake(0, 0, Operation::SET);
    static const Id transferInSwitch(0, 0, Operation::SET);
    static const Id transferOutSwitch(0, 0, Operation::SET);

    // UI Out
    static const Id transferAproached(0, 0, Operation::SET);
    static const Id transferBlocked(0, 0, Operation::SET);

    // Storage
    // In
    static const Id storageSet(0, 0, Operation::GET);

    // Out
    static const Id storageBrake(0, 0, Operation::SET);

    // UI Out
    static const Id storageAproached(0, 0, Operation::SET);
    static const Id storageBlocked(0, 0, Operation::SET);

    // Switches
    // UI In
    static const Id enterSwitch(0, 0, Operation::GET);
    static const Id exitSwitch(0, 0, Operation::GET);
}
