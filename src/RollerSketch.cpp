/*************************************************************
* Created by J. Weij
*************************************************************/
#include <Arduino.h>
#include <NodeLib/NodeMaster.h>

#include "IoConfig.h"
#include "Rollercoaster.h"

static int PIN_LED = 17;

NodeLib::NodeMaster node(2, PIN_LED);
Rollercoaster rollercoaster(node);

void setup(void)
{
    Serial.begin(115200);
    delay(2000);
    Serial.println("Setting up");

    node.Init();

    IoConfig config(node);
    config.ConfigureIo();

    rollercoaster.Init();
}

void loop(void)
{
    node.Loop();
    delay(200);
}
