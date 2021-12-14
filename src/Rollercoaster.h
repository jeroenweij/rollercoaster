/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/NodeMaster.h>
#include <tools/Logger.h>

#include "IoInput.h"
#include "IoOutput.h"
#include "Lift.h"
#include "Mode.h"
#include "Station.h"
#include "Transfer.h"

class Rollercoaster
{
  public:
    /// Constructor.
    Rollercoaster(NodeLib::NodeMaster& nodeMaster);

    /// Destructor.
    virtual ~Rollercoaster() { }

    void Init();
    void Loop();

  private:
    void DetermineMode();

    IoInput inputHandler;
    IoOutput outputHandler;

    Mode mode;
    Station station;
    Lift lift;
    Transfer transfer;
};
