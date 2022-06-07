#pragma once

#include "lsystem.h"
#include "organic.h"
#include "3d.h"
#include "stem.h"
#include "environment.h"

class Kernel : public LSystem::Node, public Organic
{
public:
    Kernel(LSystem& lsystem, float initialEnergy)
        : LSystem::Node(lsystem)
        , Organic(initialEnergy)
    {
    }

    virtual void Grow(void* userData) override
    {
        if(userData != nullptr)
        {
            Environment& environment = *reinterpret_cast<Environment*>(userData);
            ReceiveEnergy(environment.GetEnergyAtPosition(origin.position));

            if(EnergyStored() > 100)
            {
               lsystem.MorphNode<Stem>(this, EnergyStored());
            }
        }
    }
};