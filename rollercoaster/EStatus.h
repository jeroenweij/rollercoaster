/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include <ostream>

enum class EStatus
{
    EXPECTING,
    BLOCKED,
    LEAVING,
    FREE
};

inline std::ostream& operator<<(std::ostream& oStrStream, const EStatus status )
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
