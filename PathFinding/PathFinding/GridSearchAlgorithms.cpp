#include "GridSearchAlgorithms.h"

#include "DebugNew.h"
#include "Node.h"
#include "Grid.h"

#include <cassert>
#include <queue>
#include <algorithm>
#include <limits>

namespace
{
    // Returns the node with the lowest weight in the vector passed.
    SNode* GetClosestnode (const Nodes vector, const WeightVector weights)
    {
        SNode* candidate = vector[0];

        for (SNode* node : vector)
        {
            if (weights[node->index] < weights[candidate->index]) candidate = node;
        }

        return candidate;
    }

    float CalculateHeuristic (
        const SNode*                           start,
        const SNode*                           end,
        const GridSearchAlgorithms::EHeuristic heuristic)
    {
        // Added cost of crossing the start node and the end node.
        float addedCost = start->weight + end->weight;
        // The size is the same for all the nodes.
        float numXNodes =
            abs (start->position.mX - end->position.mX) / start->size;
        float numYNodes =
            abs (start->position.mY - end->position.mY) / start->size;

        switch (heuristic)
        {
        case GridSearchAlgorithms::eHeuristic_Euclidean:
            return addedCost
                * sqrt ((numXNodes * numXNodes) + (numYNodes * numYNodes));
            break;
        case GridSearchAlgorithms::eHeuristic_Manhattan:
            return addedCost * (numXNodes + numYNodes);
            break;
        default:
            break;
        }

        return std::numeric_limits<float>::infinity ();
    }

    Nodes GetPathToSource (SNode* start)
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

    Nodes GetPathToSource (Nodes startPath, Nodes goalPath)
    {
        Nodes path;

        // Reverse the goal path so that the path returned goes from goal to
        // start (like GetPathToSource (SNode* start)).
        std::reverse (goalPath.begin (), goalPath.end ());

        for (const auto& node : goalPath)
        {
            path.push_back (node);
        }

        for (const auto& node : startPath)
        {
            path.push_back (node);
        }

        return path;
    }
}

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
    queue.front ()->visited = true;

    while (queue.size () > 0)
    {
        SNode* node = queue.front ();
        queue.pop ();

        for (SNode* adjacentNode : grid->GetAdjacentNodes (node->index))
        {
            if (!adjacentNode->visited)
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
    stack.back ()->visited = true;

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
            if (!adjacentNode->visited)
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

Nodes GridSearchAlgorithms::AStar (
    CGrid* const     grid,
    const int        start,
    const int        goal,
    const EHeuristic heuristic)
{
    assert (goal >= 0);

    Nodes         openNodes;
    SNode*        startNode{ grid->GetNode (start) };
    SNode*        goalNode { grid->GetNode (goal) };
    SNode*        currentNode;
    WeightVector& weights  { grid->GetWeights () };
    WeightVector  heuristics;

    for (SNode* node : grid->GetNodes ())
    {
        node->parent         = nullptr;
        node->visited        = false;
        weights[node->index] = node->weight;
        heuristics.push_back (0.f);
    }

    openNodes.push_back (startNode);
    weights[start]     = 0.0f;
    heuristics[start]  = CalculateHeuristic (startNode, goalNode, heuristic);
    startNode->visited = true;

    if (start == goal) return Nodes{ startNode };

    while (!openNodes.empty ())
    {
        // Set the current node to point to an open node, to avoid using the
        // last current node (which has been closed).
        currentNode = openNodes.back ();

        // Use the open node with the lowest cost as the current node.
        for (SNode* node : openNodes)
        {
            if ((weights[node->index] + heuristics[node->index])
                < (weights[currentNode->index]
                    + heuristics[currentNode->index]))
            {
                currentNode = node;
            }
        }

        // Close current node.
        openNodes.erase (
            std::find (openNodes.begin (), openNodes.end (), currentNode));

        if (currentNode == goalNode) return GetPathToSource (currentNode);

        for (SNode* adjacentNode : grid->GetAdjacentNodes (currentNode->index))
        {
            float newWeight =
                weights[currentNode->index] + adjacentNode->weight;

            if (!adjacentNode->visited)
            {
                adjacentNode->parent            = currentNode;
                weights[adjacentNode->index]    = newWeight;
                heuristics[adjacentNode->index] =
                    CalculateHeuristic (adjacentNode, goalNode, heuristic);
                openNodes.push_back (adjacentNode);
                adjacentNode->visited           = true;
            }
            // Since a closed node will already have the lowest weight, only
            // the weights of the opened nodes will be modified.
            else if (newWeight < weights[adjacentNode->index])
            {
                adjacentNode->parent         = currentNode;
                weights[adjacentNode->index] = newWeight;
            }
        }
    }

    return Nodes{};
}

Nodes GridSearchAlgorithms::BiDirectionalAStar (
    CGrid* const     grid,
    const int        start,
    const int        goal,
    const EHeuristic heuristic)
{
    assert (goal >= 0);

    Nodes         startOpenNodes;
    Nodes         goalOpenNodes;
    Nodes         startClosedNodes;
    Nodes         goalClosedNodes;
    SNode*        startNode{ grid->GetNode (start) };
    SNode*        goalNode { grid->GetNode (goal) };
    SNode*        currentNode;
    WeightVector& weights  { grid->GetWeights () };
    WeightVector  heuristics;

    for (SNode* node : grid->GetNodes ())
    {
        node->parent         = nullptr;
        node->visited        = false;
        weights[node->index] = node->weight;
        heuristics.push_back (0.f);
    }

    startOpenNodes.push_back (startNode);
    weights[start]     = 0.0f;
    heuristics[start]  = CalculateHeuristic (startNode, goalNode, heuristic);
    startNode->visited = true;

    goalOpenNodes.push_back (goalNode);
    weights[goal]     = 0.0f;
    heuristics[goal]  = CalculateHeuristic (goalNode, startNode, heuristic);
    goalNode->visited = true;

    if (start == goal) return Nodes{ startNode };

    while (!startOpenNodes.empty () && !goalOpenNodes.empty ())
    {
        // Set the current node to point to an open node, to avoid using the
        // last goal node.
        currentNode = startOpenNodes.back ();

        // Use the open node with the lowest cost as the current node.
        for (SNode* node : startOpenNodes)
        {
            if ((weights[node->index] + heuristics[node->index])
                < (weights[currentNode->index]
                    + heuristics[currentNode->index]))
            {
                currentNode = node;
            }
        }

        // Close current start node.
        startOpenNodes.erase (
            std::find (
                startOpenNodes.begin ()
                , startOpenNodes.end ()
                , currentNode));
        startClosedNodes.push_back (currentNode);

        for (SNode* adjacentNode : grid->GetAdjacentNodes (currentNode->index))
        {
            float newWeight =
                weights[currentNode->index] + adjacentNode->weight;

            if (!adjacentNode->visited)
            {
                adjacentNode->parent            = currentNode;
                weights[adjacentNode->index]    = newWeight;
                heuristics[adjacentNode->index] =
                    CalculateHeuristic (adjacentNode, goalNode, heuristic);
                startOpenNodes.push_back (adjacentNode);
                adjacentNode->visited           = true;
            }
            // If the adjacent node belongs to the frontier from the goal,
            // return path.
            else if (std::find (
                goalClosedNodes.begin ()
                , goalClosedNodes.end ()
                , adjacentNode)
                != goalClosedNodes.end ())
            {
                Nodes startPath{ GetPathToSource (currentNode) };
                Nodes goalPath { GetPathToSource (adjacentNode) };
                return GetPathToSource (startPath, goalPath);
            }
            // Since a closed node will already have the lowest weight, only
            // the weights of the opened nodes will be modified.
            else if (newWeight < weights[adjacentNode->index])
            {
                adjacentNode->parent         = currentNode;
                weights[adjacentNode->index] = newWeight;
            }
        }

        // Set the current node to point to an open node, to avoid using the
        // last start node.
        currentNode = goalOpenNodes.back ();

        // Use the open node with the lowest cost as the current node.
        for (SNode* node : goalOpenNodes)
        {
            if ((weights[node->index] + heuristics[node->index])
                < (weights[currentNode->index]
                    + heuristics[currentNode->index]))
            {
                currentNode = node;
            }
        }

        // Close current goal node.
        goalOpenNodes.erase (
            std::find (
                goalOpenNodes.begin ()
                , goalOpenNodes.end ()
                , currentNode));
        goalClosedNodes.push_back (currentNode);

        for (SNode* adjacentNode : grid->GetAdjacentNodes (currentNode->index))
        {
            float newWeight =
                weights[currentNode->index] + adjacentNode->weight;

            if (!adjacentNode->visited)
            {
                adjacentNode->parent            = currentNode;
                weights[adjacentNode->index]    = newWeight;
                heuristics[adjacentNode->index] =
                    CalculateHeuristic (adjacentNode, startNode, heuristic);
                goalOpenNodes.push_back (adjacentNode);
                adjacentNode->visited           = true;
            }
            // If the adjacent node belongs to the frontier from the start,
            // return path.
            else if (std::find (
                startClosedNodes.begin ()
                , startClosedNodes.end ()
                , adjacentNode)
                != startClosedNodes.end ())
            {
                Nodes goalPath { GetPathToSource (currentNode) };
                Nodes startPath{ GetPathToSource (adjacentNode) };
                return GetPathToSource (startPath, goalPath);
            }
            // Since a closed node will already have the lowest weight, only
            // the weights of the opened nodes will be modified.
            else if (newWeight < weights[adjacentNode->index])
            {
                adjacentNode->parent = currentNode;
                weights[adjacentNode->index] = newWeight;
            }
        }
    }

    return Nodes{};
}