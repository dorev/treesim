#pragma once

#include "organismgraph.h"
#include "environment.h"

enum class PlantAnatomy
{
    Kernel,
    Stem,
    StemNode,
    LeafBud,
    Leaf,
    FlowerBud,
    Flower,
    TerminalBud
};

#define DECLARE_ANATOMY_ID(plantAnatomyEnum) \
static constexpr PlantAnatomy anatomyId = PlantAnatomy::plantAnatomyEnum

class LeafBud : public OrganismGraph::Node
{
public:
    DECLARE_ANATOMY_ID(LeafBud);

    LeafBud(OrganismGraph& organism, float initialEnergy)
        : OrganismGraph::Node(organism, initialEnergy)
    {
    }

    virtual void Grow(Environment& environment) override
    {
        ReceiveEnergy(environment.GetEnergyAtPosition(origin));
    }
};

class StemNode : public OrganismGraph::Node
{
public:
    DECLARE_ANATOMY_ID(StemNode);

    StemNode(OrganismGraph& organism, float initialEnergy)
        : OrganismGraph::Node(organism, initialEnergy)
    {
    }

    virtual void Grow(Environment& environment) override
    {
        ReceiveEnergy(environment.GetEnergyAtPosition(origin));
    }
};

class Stem : public OrganismGraph::Node
{
public:
    DECLARE_ANATOMY_ID(Stem);

    Stem(OrganismGraph& organism, float initialEnergy)
        : OrganismGraph::Node(organism, initialEnergy)
        , _length(1)
        , _maxLength(20)
        , _growthModifier(0.2f)
        , _hasSpawnedNode(false)
        , _isFullyGrown(false)
    {
    }

    virtual void Grow(Environment& environment) override
    {
        ReceiveEnergy(environment.GetEnergyAtPosition(origin));

        GrowInternal();
        UpdateShape();
        SpawnNode();
        UpdateChildrenPositions();
        TransferEnergyToChildren();
    }

private:
    void GrowInternal()
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
            _isFullyGrown = true;

            // Consume some energy
            LoseEnergy(2);
        }
    }

    void UpdateShape()
    {

    }

    void SpawnNode()
    {
        if(EnergyStored() < 100 || _hasSpawnedNode)
        {
            return;
        }

        SharedPtr<StemNode> stemNode = organism.AppendToNode<StemNode>(this, 0.0f);
        if (stemNode)
        {
            TransferEnergy(*stemNode, 75.0f);
            _hasSpawnedNode = true;

            // Set StemNode position

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

    void TransferEnergyToChildren()
    {
        // Send remaining energy to children
        if(EnergyStored() > 0)
        {
        }
    }

private:
    PosQuat end;
    float _length;
    float _maxLength;
    float _growthModifier;
    bool _hasSpawnedNode;
    bool _isFullyGrown;
};

class TerminalBud : public OrganismGraph::Node
{
public:
    DECLARE_ANATOMY_ID(TerminalBud);

    TerminalBud(OrganismGraph& organism, float initialEnergy)
        : OrganismGraph::Node(organism, initialEnergy)
    {
    }

    virtual void Grow(Environment& environment) override
    {
        ReceiveEnergy(environment.GetEnergyAtPosition(origin));
    }
};

class Kernel : public OrganismGraph::Node
{
public:
    DECLARE_ANATOMY_ID(Kernel);

    Kernel(OrganismGraph& organism, float initialEnergy)
        : OrganismGraph::Node(organism, initialEnergy)
    {
    }

    virtual void Grow(Environment& environment) override
    {
        ReceiveEnergy(environment.GetEnergyAtPosition(origin));
        if(EnergyStored() > 100)
        {
           SharedPtr<TerminalBud> terminalBud = organism.AppendToNode<TerminalBud>(this, 0.0f);
           if(terminalBud)
           {
               children.push_back(terminalBud);
           }
           organism.MorphNode<Stem>(this, EnergyStored());
        }
    }
};
