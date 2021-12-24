/*************************************************************
* Created by J. Weij
*************************************************************/

#include "Gates.h"
#include "IoConfig.h"
#include <pins.h>

Gates::Gates(IoOutput& output) :
    button(PIN_GATE_BUTTON, PIN_GATE_BUTTON_LED),
    opened(false),
    buttonPressed(false),
    output(output)
{
}

void Gates::Init()
{
    button.Init();
    SetOpen(false);
}

void Gates::Check(const bool canMove)
{
    button.SetLed(canMove);

    if (IsOpen() && !canMove)
    {
        SetOpen(false);
    }
    if (canMove)
    {
        if (button.IsPressed())
        {
            if (!buttonPressed)
            {
                SetOpen(!opened);
                buttonPressed = true;
            }
        }
        else
        {
            if (buttonPressed)
            {
                buttonPressed = false;
            }
        }
    }
}

const bool Gates::IsOpen()
{
    return opened;
}

void Gates::SetOpen(const bool open)
{
    opened = open;
    output.writeTwostate(NodeId::stationGates.id, opened);
}
