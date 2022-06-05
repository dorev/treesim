#pragma once

#include "types.h"
#include "3d.h"

#include <algorithm>

class LSystem
{
public:
    struct Node
    {
        LSystem& lsystem;
        PosQuat origin;
        PosQuat end;
        SharedPtr<Node> source;
        Vector<SharedPtr<Node>> edges;

        Node(LSystem& lsystem) : lsystem(lsystem)
        {
        }

        virtual ~Node()
        {
        }

        virtual void Grow(void* userData) = 0;
    };

    using Iterator = Vector<SharedPtr<Node>>::iterator;

public:

    template <class T, class... Args>
    void Init(Args... args)
    {
        _nodes.clear();
        _nodes.emplace_back(SharedPtr<T>(new T(*this, std::forward<Args>(args)...)));
        _nodesEndIndex = 1;
    }

    template <class T, class... Args>
    void MorphNode(Node* morphingNode, Args... args)
    {
        if(morphingNode == nullptr)
        {
            return;
        }

        for(unsigned i = 0; i < _nodesEndIndex; ++i)
        {
            if(_nodes[i].get() == morphingNode)
            {
                SharedPtr<T> newNode(new T(*this, std::forward<Args>(args)...));

                // Obtain l-system links to other nodes from morphing node
                newNode->source = morphingNode->source;
                newNode->edges = morphingNode->edges;

                // Update this edge in source node
                if (newNode->source != nullptr)
                {
                    for(SharedPtr<Node> edge : newNode->source->edges)
                    {
                        if(edge.get() == morphingNode)
                        {
                            edge = newNode;
                            break;
                        }
                    }
                }

                // Update source node of edge nodes
                for(SharedPtr<Node> edge : morphingNode->edges)
                {
                    edge->source = newNode;
                }

                // Replace morphing node with new node
                _nodes[i] = newNode;
                break;
            }
        }
    }

    void Reserve(unsigned size)
    {
        _nodes.reserve(size);
    }

    void Grow(unsigned n = 1, void* userData = nullptr)
    {
        if(_nodes.empty())
        {
            return;
        }

        while(n--)
        {
            _isFragmented = false; 

            for(unsigned i = 0; i < _nodes.size(); ++i)
            {
                if(_nodes[i] != nullptr)
                {
                    _nodes[i]->Grow(userData);
                }
                else if(i < _nodesEndIndex && !_isFragmented)
                {
                    // mark as fragmented if other valid nodes are left
                    _isFragmented = true;
                }
                else
                {
                    // we're beyond the last valid node, so there is nothing left to process
                    break;
                }
            }

            if(_isFragmented)
            {
                Defragment();
            }
        }
    }

private:
    void Defragment()
    {
        const Iterator end = std::stable_partition(
            _nodes.begin(),
            _nodes.end(),
            [](const SharedPtr<Node>& node) { return node != nullptr; }
        );

        _nodesEndIndex = static_cast<unsigned>(end - _nodes.begin());
        _isFragmented = false;
    }

private:
    Vector<SharedPtr<Node>> _nodes;
    unsigned _nodesEndIndex;
    bool _isFragmented;
};
