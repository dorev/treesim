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
        Position3D origin;
        SharedPtr<Node> parent;
        Vector<SharedPtr<Node>> edges;

        Node(LSystem& lsystem) : lsystem(lsystem)
        {
        }

        virtual ~Node()
        {
        }

        virtual void Grow(void* userData) = 0;
    };

    using Iterator = List<SharedPtr<Node>>::iterator;

public:

    template <class T, class... Args>
    void Init(Args... args)
    {
        _nodes.clear();
        _nodes.emplace_back(SharedPtr<T>(new T(*this, std::forward<Args>(args)...)));
    }

    SharedPtr<Node> FindNode(Node* nodeToFind)
    {
        if (nodeToFind != nullptr)
        {
            for (SharedPtr<Node>& node : _nodes)
            {
                if (node.get() == nodeToFind)
                {
                    return node;
                }
            }
        }
        return nullptr;
    }

    Iterator FindNodeIterator(Node* nodeToFind)
    {
        if (nodeToFind != nullptr)
        {
            for (Iterator itr = _nodes.begin(); itr != _nodes.end(); ++itr)
            {
                if (itr->get() == nodeToFind)
                {
                    return itr;
                }
            }
        }
        return _nodes.end();
    }

    template <class T, class... Args>
    void MorphNode(Node* node, Args... args)
    {
        static_assert(std::is_base_of<LSystem::Node, T>::value);

        SharedPtr<Node> morphingNode = FindNode(node);
        if(morphingNode == nullptr)
        {
            return;
        }

        SharedPtr<Node> newNode(new T(*this, std::forward<Args>(args)...));

        // Obtain l-system links to other nodes from morphing node
        newNode->parent = morphingNode->parent;
        newNode->edges = morphingNode->edges;

        // Update this edge in source node
        if (newNode->parent != nullptr)
        {
            for(SharedPtr<Node>& edge : newNode->parent->edges)
            {
                if(edge == morphingNode)
                {
                    edge = newNode;
                    break;
                }
            }
        }

        // Update source node of edge nodes
        for(SharedPtr<Node> edge : morphingNode->edges)
        {
            edge->parent = newNode;
        }

        ReplaceNode(morphingNode, newNode);
    }

    void ReplaceNode(SharedPtr<Node>& originalNode, SharedPtr<Node>& newNode)
    {
        Iterator itr = std::find(_nodes.begin(), _nodes.end(), originalNode);
        if (itr != _nodes.end())
        {
            (*itr) = newNode;
        }
    }

    template <class T, class... Args>
    SharedPtr<T> AppendToNode(Node * node, Args... args)
    {
        static_assert(std::is_base_of<LSystem::Node, T>::value);

        Iterator originNodeIterator = FindNodeIterator(node);
        if (originNodeIterator == _nodes.end())
        {
            return nullptr;
        }

        SharedPtr<T> newNode(new T(*this, std::forward<Args>(args)...));
        newNode->parent = *originNodeIterator;

        _nodes.insert(++originNodeIterator, newNode);
        return newNode;
    }

    void Grow(unsigned n = 1, void* userData = nullptr)
    {
        if(_nodes.empty())
        {
            return;
        }

        while(n--)
        {
            for(SharedPtr<Node>& node : _nodes)
            {
                if(node != nullptr)
                {
                    node->Grow(userData);
                }
            }
        }
    }

private:
    List<SharedPtr<Node>> _nodes;
};
