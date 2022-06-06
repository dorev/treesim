#pragma once

#include "3d.h"

class Environment
{
public:
    float GetEnergyAtPosition(const Vector3& position)
    {
        (void)position;
        return 10;
    }
};
