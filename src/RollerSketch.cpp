/*************************************************************
* Created by J. Weij
*************************************************************/
#include <Arduino.h>
#include <NodeLib/NodeMaster.h>
#include <tools/Logger.h>

#include "IoConfig.h"
#include "Rollercoaster.h"

static int PIN_LED = 13;
static int ENABLE_PIN = 3;

NodeLib::NodeMaster node(ENABLE_PIN);
Rollercoaster rollercoaster(node);

void setup(void)
{
    pinMode(ENABLE_PIN, OUTPUT);
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(ENABLE_PIN, LOW);
    digitalWrite(PIN_LED, LOW);

    Serial.begin(115200);
    LOG_INFO(F("Wait for nodes"));
    delay(1000);
    LOG_INFO(F("Setting up"));
    LOG_DEBUG(F("Debug log enabled"));

    digitalWrite(PIN_LED, HIGH);
    node.Init();
    digitalWrite(PIN_LED, LOW);

    IoConfig config(node);
    config.ConfigureIo();

    rollercoaster.Init();
    node.StartPollingNodes();
}

void loop(void)
{
    digitalWrite(PIN_LED, HIGH);
    node.Loop();
    delay(200);
}
