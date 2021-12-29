/*************************************************************
* Created by J. Weij
*************************************************************/
#include <Arduino.h>
#include <NodeLib/NodeMaster.h>
#include <pins.h>
#include <tools/Logger.h>

#include "IoConfig.h"
#include "Rollercoaster.h"

NodeLib::NodeMaster node(PIN_ENABLE_385, PIN_LED, PIN_E_STOP_RESET_LED, PIN_E_STOP_RESET);
Rollercoaster       rollercoaster(node);

void setup(void)
{
    pinMode(PIN_ENABLE_385, OUTPUT);
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_ENABLE_385, LOW);
    digitalWrite(PIN_LED, HIGH);

    Serial.begin(115200);
    LOG_INFO(F("Wait for nodes"));
    delay(1000);
    LOG_INFO(F("Setting up"));
    LOG_DEBUG(F("Debug log enabled"));

    node.Init(6);
    rollercoaster.Init();
    digitalWrite(PIN_LED, LOW);

    IoConfig config(node);
    config.ConfigureIo();

    node.StartPollingNodes();
    LOG_INFO(F("Setup complete"));
}

void loop(void)
{
    digitalWrite(PIN_LED, HIGH);
    node.Loop();
    rollercoaster.Loop();
}
