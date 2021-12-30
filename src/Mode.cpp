/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Mode.h"
#include "Arduino.h"
#include <pins.h>
#include <tools/Logger.h>

EMode Mode::mode = EMode::OFF;

Mode::Mode() :
    numBlocks(0)
{
    Init();
    digitalWrite(PIN_E_STOP_RESET_LED, HIGH);
}

void Mode::Init()
{
    pinMode(PIN_MODE_AUTO, INPUT_PULLUP);
    pinMode(PIN_MODE_MANUAL, INPUT_PULLUP);
    pinMode(PIN_E_STOP, INPUT_PULLUP);
    pinMode(PIN_E_STOP_INV, INPUT_PULLUP);
    pinMode(PIN_E_STOP_RESET, INPUT_PULLUP);
    pinMode(PIN_E_STOP_RESET_LED, OUTPUT);
    digitalWrite(PIN_E_STOP_RESET_LED, LOW);
}

void Mode::Loop()
{
    EMode newMode = EMode::OFF;

    if (mode == EMode::STOP)
    {
        newMode = EMode::STOP;
        if (!EStopPressed())
        {

            if (digitalRead(PIN_E_STOP_RESET))
            {
                digitalWrite(PIN_E_STOP_RESET_LED, HIGH);
            }
            else
            {
                digitalWrite(PIN_E_STOP_RESET_LED, LOW);
                newMode = EMode::OFF;
            }
        }
    }
    else
    {
        if (EStopPressed())
        {
            newMode = EMode::STOP;
        }
        else if (!digitalRead(PIN_MODE_MANUAL))
        {
            newMode = EMode::MANUAL;
        }
        else if (!digitalRead(PIN_MODE_AUTO))
        {
            newMode = EMode::AUTO;
        }
    }

    if (mode != newMode)
    {
        LOG_INFO(F("Mode change ") << mode << " -> " << newMode);
        mode = newMode;

        if (mode == EMode::AUTO)
        {
            ResetRestart();
        }
    }
}

void Mode::ResetRestart()
{
    for (int i = 0; i < numBlocks; i++)
    {
        blocks[i]->ResetStop();
    }
}

const bool Mode::EStopPressed()
{
    return !digitalRead(PIN_E_STOP) || digitalRead(PIN_E_STOP_INV);
}

void Mode::AddResetCallback(IBlock* block)
{
    if (numBlocks < 5)
    {
        blocks[numBlocks] = block;
        numBlocks++;
    }
    else
    {
        LOG_ERROR(F("Error adding reset callback"));
    }
}

const EMode Mode::GetMode()
{
    return mode;
}

const bool Mode::IsManual()
{
    return mode == EMode::MANUAL;
}

const bool Mode::IsAuto()
{
    return mode == EMode::AUTO;
}

const bool Mode::IsStop()
{
    return mode == EMode::STOP;
}

const bool Mode::IsOn()
{
    return mode == EMode::MANUAL || mode == EMode::AUTO;
}

const bool Mode::Error()
{
    mode = EMode::STOP;
    LOG_ERROR(F("ERROR"));
}
