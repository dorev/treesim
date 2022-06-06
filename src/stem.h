#pragma once

#include <iostream>

#include "lsystem.h"
#include "environment.h"
#include "organic.h"

class Bud : public LSystem::Node, public Organic
{
public:
    Bud(LSystem& lsystem, float initialEnergy)
        : LSystem::Node(lsystem)
        , Organic(initialEnergy)
    {
    }

    virtual void Grow(void* userData) override
    {
        if(userData != nullptr)
        {
            Environment& environment = *reinterpret_cast<Environment*>(userData);
            GiveEnergy(environment.GetEnergyAtPosition(origin.position));
        }
    }
};

class Stem : public LSystem::Node, public Organic
{
public:
    Stem(LSystem& lsystem, float initialEnergy)
        : LSystem::Node(lsystem)
        , Organic(initialEnergy)
    {
    }

    virtual void Grow(void* userData) override
    {
        if(userData != nullptr)
        {
            Environment& environment = *reinterpret_cast<Environment*>(userData);
            GiveEnergy(environment.GetEnergyAtPosition(origin.position));

            if(GetEnergy() > 100)
            {
                SharedPtr<Bud> bud = lsystem.AppendToNode<Bud>(this, 0.0f);
                if (bud != nullptr)
                {
                    TransferEnergy(*bud, 75.0f);
                    // Position
                }
            }
        }
    }
};
