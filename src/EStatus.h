/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "WString.h"
#include <tools/SStream.h>

enum class EStatus
{
    EXPECTING,
    BLOCKED,
    LEAVING,
    FREE,
};

inline std::stringstream& operator<<(std::stringstream& oStrStream, const EStatus status )
{
    switch (status)
    {
        case EStatus::EXPECTING:
            oStrStream << "EXPECTING";
            break;
        case EStatus::BLOCKED:
            oStrStream << "BLOCKED";
            break;
        case EStatus::LEAVING:
            oStrStream << "LEAVING";
            break;
        case EStatus::FREE:
            oStrStream << "FREE";
            break;

    }

    return oStrStream;
}
