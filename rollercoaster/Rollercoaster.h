/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/NodeMaster.h>

#include "Logger.h"
#include "IoInput.h"
#include "IoOutput.h"

#include "Station.h"
#include "Lift.h"
#include "Transfer.h"

class Rollercoaster
{
    public:
        /// Constructor.
        Rollercoaster(NodeLib::NodeMaster& nodeMaster);

        /// Destructor.
        virtual ~Rollercoaster() {}

        void Stop();

    private:

        IoInput inputHandler;
        IoOutput outputHandler;

        Station station;
        Lift lift;
        Transfer transfer;

        /// <summary>Example log zone.</summary>
        Logger& logZone;

};
