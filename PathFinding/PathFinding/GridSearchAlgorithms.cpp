#include "GridSearchAlgorithms.h"

#include "DebugNew.h"
#include "Node.h"
#include "Grid.h"

#include <cassert>
#include <queue>
#include <algorithm>
#include <limits>

Nodes GridSearchAlgorithms::BreadthFirstSearch (
    CGrid* const grid,
    const int    start,
    const int    goal)
{
    assert (start >= 0);

    WeightVector& weights{ grid->GetWeights () };

    for (SNode* node : grid->GetNodes ())
    {
        node->parent         = nullptr;
        node->visited        = false;
        weights[node->index] = node->weight;
    }

    weights[start] = 0.f;

    if (start == goal) return Nodes{ grid->GetNode (start) };

    std::queue<SNode*> queue;
    queue.push (grid->GetNode (start));

    while (queue.size () > 0)
    {
        SNode* node = queue.front ();
        queue.pop ();

        for (SNode* adjacentNode : grid->GetAdjacentNodes (node->index))
        {
            if (adjacentNode->visited == false)
            {
                adjacentNode->parent         = node;
                weights[adjacentNode->index] =
                    weights[node->index] + adjacentNode->weight;
                adjacentNode->visited        = true;

                if ((goal != -1) && (adjacentNode == grid->GetNode (goal)))
                {
                    return GetPathToSource (adjacentNode);
                }

                queue.push (adjacentNode);
            }
        }
        node->visited = true;
    }

    // No path to goal node exists.
    return Nodes{};
}

Nodes GridSearchAlgorithms::DepthFirstSearch (
    CGrid* const grid,
    const int    start,
    const int    goal,
    const bool   searchFromRight)
{
    WeightVector& weights{ grid->GetWeights () };

    for (SNode* node : grid->GetNodes ())
    {
        node->parent         = nullptr;
        node->visited        = false;
        weights[node->index] = node->weight;
    }

    weights[start] = 0.f;

    if (start == goal) return Nodes{ grid->GetNode (start) };

    Nodes stack;
    stack.push_back (grid->GetNode (start));

    while (stack.size () > 0)
    {
        SNode* node = stack.back ();
        stack.pop_back ();

        Nodes adjacentNodes = grid->GetAdjacentNodes (node->index);
        if (searchFromRight == true)
        {
            std::reverse (adjacentNodes.begin (), adjacentNodes.end ());
        }
        for (SNode* adjacentNode : adjacentNodes)
        {
            if (adjacentNode->visited == false)
            {
                adjacentNode->parent         = node;
                weights[adjacentNode->index] =
                    weights[node->index] + adjacentNode->weight;
                adjacentNode->visited        = true;

                if ((goal != -1) && (adjacentNode == grid->GetNode (goal)))
                {
                    return GetPathToSource (adjacentNode);
                }

                stack.push_back (adjacentNode);
            }
        }
        node->visited = true;
    }

    // No path to goal node exists.
    return Nodes{};
}

Nodes GridSearchAlgorithms::Dijkstra (
    CGrid* const grid,
    const int    start,
    const int    goal)
{
    Nodes         unfinishedNodes;
    WeightVector& weights{ grid->GetWeights () };

    for (SNode* node : grid->GetNodes ())
    {
        node->parent  = nullptr;
        node->visited = false;
        unfinishedNodes.push_back (node);
    }

    for (float& weight : weights)
    {
        weight = std::numeric_limits<float>::infinity ();
    }

    weights[grid->GetNode (start)->index] = 0.f;
    grid->GetNode (start)->visited        = true;

    if (start == goal) return Nodes{ grid->GetNode (start) };

    while (unfinishedNodes.size () > 0)
    {
        SNode* node = GetClosestnode (unfinishedNodes, weights);

        unfinishedNodes.erase (
            std::remove (
                unfinishedNodes.begin ()
                , unfinishedNodes.end ()
                , node)
            , unfinishedNodes.end ());

        if ((goal != -1) && (node == grid->GetNode (goal)))
        {
            return GetPathToSource (node);
        }

        for (SNode* adjacentNode : grid->GetAdjacentNodes (node->index))
        {
            if (weights[adjacentNode->index] >
                (weights[node->index] + adjacentNode->weight))
            {
                weights[adjacentNode->index] =
                    weights[node->index] + adjacentNode->weight;
                adjacentNode->parent         = node;
                adjacentNode->visited        = true;
            }
        }
    }
    return Nodes{};
}

SNode* GridSearchAlgorithms::GetClosestnode (
    const Nodes        vector,
    const WeightVector weights)
{
    SNode* candidate = vector[0];

    for (SNode* node : vector)
    {
        if (weights[node->index] < weights[candidate->index]) candidate = node;
    }

    return candidate;
}

Nodes GridSearchAlgorithms::GetPathToSource (SNode* start)
{
    Nodes  path;
    SNode* next = start;

    while (next != nullptr)
    {
        path.push_back (next);
        next = next->parent;
    }

    return path;
}