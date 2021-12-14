/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "WString.h"
#include <tools/SStream.h>

enum class EMode
{
    OFF,
    MANUAL,
    AUTO,
    STOP,
};

inline std::stringstream& operator<<(std::stringstream& oStrStream, const EMode status)
{
    switch (status)
    {
        case EMode::OFF:
            oStrStream << "OFF";
            break;
        case EMode::MANUAL:
            oStrStream << "MANUAL";
            break;
        case EMode::AUTO:
            oStrStream << "AUTO";
            break;
        case EMode::STOP:
            oStrStream << "STOP";
            break;
    }

    return oStrStream;
}
