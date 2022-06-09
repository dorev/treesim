#pragma once

#include "3d.h"

class Environment
{
public:
    float GetEnergyAtPosition(const PosQuat& position)
    {
        (void)position;
        return 20;
    }
};
