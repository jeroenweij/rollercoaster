/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <NodeLib/NodeMaster.h>
#include <NodeLib/id.h>
#include <tools/Logger.h>

class IoOutput
{
  public:
    IoOutput(NodeLib::NodeMaster& node);
    ~IoOutput() { }

    void SetOutput(const NodeLib::Id& id);
    void writeTwostate(const NodeLib::Id& id, bool value);
    void WriteValue(const NodeLib::Id& id, Value value);

  private:
    NodeLib::NodeMaster& node;
};
