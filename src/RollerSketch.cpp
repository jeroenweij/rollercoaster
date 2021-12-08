/*************************************************************
* Created by J. Weij
*************************************************************/
#include <Arduino.h>
#include <NodeLib/NodeMaster.h>

#include "IoConfig.h"
#include "Rollercoaster.h"

static int PIN_LED = 13;

NodeLib::NodeMaster node(PIN_LED);
Rollercoaster rollercoaster(node);

void setup(void)
{
    pinMode(PIN_LED, OUTPUT);
    Serial.begin(115200);
    Serial.println(F("Wait for nodes"));
    delay(1000);
    Serial.println(F("Setting up"));

    node.Init();

    IoConfig config(node);
    config.ConfigureIo();

    rollercoaster.Init();
}

void loop(void)
{
    digitalWrite(PIN_LED, HIGH);
    node.Loop();
    delay(200);
}
