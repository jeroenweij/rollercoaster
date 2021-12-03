/*************************************************************
* Created by J. Weij
*************************************************************/
#include <Arduino.h>
#include <NodeLib/NodeMaster.h>
#include "Rollercoaster.h"

NodeLib::NodeMaster node(2);
Rollercoaster rollercoaster(node);

void setup(void)
{

    node.Init();
    rollercoaster.Stop();
}

void loop(void)
{
    node.Loop();
    delay(200);
}
