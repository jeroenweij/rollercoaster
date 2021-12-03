/*************************************************************
* Created by J. Weij
*************************************************************/

#pragma once

#include "WString.h"

enum class EStatus
{
    EXPECTING,
    BLOCKED,
    LEAVING,
    FREE,
};

inline String EStatusToString(EStatus status)
{
    switch (status)
    {
        case EStatus::EXPECTING:
            return "EXPECTING";
            break;
        case EStatus::BLOCKED:
            return "BLOCKED";
            break;
        case EStatus::LEAVING:
            return "LEAVING";
            break;
        case EStatus::FREE:
            return "FREE";
            break;
    }
}
