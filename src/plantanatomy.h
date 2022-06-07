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
        if(userData == nullptr)
        {
            return;
        }

        Environment& environment = *reinterpret_cast<Environment*>(userData);
        ReceiveEnergy(environment.GetEnergyAtPosition(origin.position));
    }
};

class StemNode : public LSystem::Node, public Organic
{
public:
    StemNode(LSystem& lsystem, float initialEnergy)
        : LSystem::Node(lsystem)
        , Organic(initialEnergy)
    {
    }

    virtual void Grow(void* userData) override
    {
        if(userData == nullptr)
        {
            return;
        }

        Environment& environment = *reinterpret_cast<Environment*>(userData);
        ReceiveEnergy(environment.GetEnergyAtPosition(origin.position));
    }
};

class Stem : public LSystem::Node, public Organic
{
public:
    Stem(LSystem& lsystem, float initialEnergy)
        : LSystem::Node(lsystem)
        , Organic(initialEnergy)
        , _length(1)
        , _maxLength(20)
        , _growthModifier(0.2f)
        , _hasSpawnedNode(false)
    {
    }

    virtual void Grow(void* userData) override
    {
        if(userData == nullptr)
        {
            return;
        }

        Environment& environment = *reinterpret_cast<Environment*>(userData);
        ReceiveEnergy(environment.GetEnergyAtPosition(origin.position));

        UseEnergy();
        SpawnNode();
        UpdateChildrenPositions();
    }

private:
    void UseEnergy()
    {
        if (EnergyStored() < 5)
        {
            return;
        }

        if (_length < _maxLength)
        {
            _length += _growthModifier * LoseEnergy(5);
        }
        else
        {
            // Send energy to neighbors
        }
    }

    void SpawnNode()
    {
        if(EnergyStored() < 100 || _hasSpawnedNode)
        {
            return;
        }

        SharedPtr<StemNode> stemNode = lsystem.AppendToNode<StemNode>(this, 0.0f);
        if (stemNode != nullptr)
        {
            TransferEnergy(*stemNode, 75.0f);
            // Set StemNode position
            _hasSpawnedNode = true;
        }
    }

    void UpdateChildrenPositions()
    {
        if (children.empty())
        {
            return;
        }

        // Update children positions if necessary
    }

private:
    float _length;
    float _maxLength;
    float _growthModifier;
    bool _hasSpawnedNode;
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
        if(userData == nullptr)
        {
            return;
        }

        Environment& environment = *reinterpret_cast<Environment*>(userData);
        ReceiveEnergy(environment.GetEnergyAtPosition(origin.position));

        if(EnergyStored() > 100)
        {
           lsystem.MorphNode<Stem>(this, EnergyStored());
        }
    }
};
