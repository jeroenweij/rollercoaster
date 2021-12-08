/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/NodeMaster.h>

#include "IoInput.h"
#include "IoOutput.h"
#include <tools/Logger.h>

#include "Lift.h"
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
    IoInput inputHandler;
    IoOutput outputHandler;

    Station station;
    Lift lift;
    Transfer transfer;
};
