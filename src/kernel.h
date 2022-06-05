#pragma once

#include <iostream>

#include "lsystem.h"
#include "organic.h"
#include "3d.h"

class Environment
{
public:
    float GetEnergyAtPosition(const Position& position)
    {
        (void)position;
        return 10;
    }
};

class Sprout : public LSystem::Node, public Organic
{
public:
    Sprout(LSystem& lsystem, float initialEnergy)
        : LSystem::Node(lsystem)
        , Organic(initialEnergy)
    {
    }

    virtual void Grow(void* userData) override
    {
        (void)userData;
        std::cout << "Hello L-System!!\n";
    }
};

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
            GiveEnergy(environment.GetEnergyAtPosition(origin.position));
        }
        else
        {
            GiveEnergy(1);
        }

        if(GetEnergy() > 100)
        {
            lsystem.MorphNode<Sprout>(this, GetEnergy());
        }
    }
};