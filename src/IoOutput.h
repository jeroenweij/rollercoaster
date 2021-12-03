/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <tools/Logger.h>
#include <NodeLib/NodeMaster.h>
#include <NodeLib/id.h>

class IoOutput
{
  public:
    IoOutput(NodeLib::NodeMaster& node);
    ~IoOutput() { }

    void SetOutput(const NodeLib::Id& id);
    void writeTwostate(const NodeLib::Id& id, bool value);

  private:
    NodeLib::NodeMaster& node;
};
