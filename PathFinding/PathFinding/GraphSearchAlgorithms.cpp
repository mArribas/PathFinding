#include "GraphSearchAlgorithms.h"

#include "DebugNew.h"
#include "Node.h"
#include "Graph.h"

#include <queue>
#include <algorithm>
#include <limits>

namespace
{
    // Returns the node with the lowest weight in the vector passed.
    SNode* GetClosestnode (const Nodes vector)
    {
        SNode* candidate = vector[0];

        for (SNode* node : vector)
        {
            if (node->weight < candidate->weight) candidate = node;
        }

        return candidate;
    }
}

Nodes GraphSearchAlgorithms::BreadthFirstSearch (
    CGraph* const graph,
    SNode* const  start,
    SNode* const  goal)
{
    for (SNode* node : graph->GetNodes ())
    {
        node->parent  = nullptr;
        node->weight  = 0.0f;
        node->visited = false;
    }

    if (start == goal) return Nodes{ start };

    std::queue<SNode*> queue;
    queue.push (start);
    queue.front ()->visited = true;

    while (queue.size () > 0)
    {
        SNode* node = queue.front ();
        queue.pop ();

        for (SNode* adjacentNode : graph->GetAdjacentNodes (node))
        {
            if (!adjacentNode->visited)
            {
                adjacentNode->parent  = node;
                adjacentNode->weight  =
                    node->weight + graph->GetEdgeWeight (node, adjacentNode);
                adjacentNode->visited = true;

                if (adjacentNode == goal)
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

Nodes GraphSearchAlgorithms::DepthFirstSearch (
    CGraph* const graph,
    SNode* const  start,
    SNode* const  goal,
    const bool    searchFromRight)
{
    for (SNode* node : graph->GetNodes ())
    {
        node->parent  = nullptr;
        node->weight  = 0.0f;
        node->visited = false;
    }

    if (start == goal) return Nodes{ start };

    Nodes stack;
    stack.push_back (start);
    stack.back ()->visited = true;

    while (stack.size () > 0)
    {
        SNode* node = stack.back ();
        stack.pop_back ();

        Nodes adjacentNodes = graph->GetAdjacentNodes (node);
        if (searchFromRight == true)
        {
            std::reverse (adjacentNodes.begin (), adjacentNodes.end ());
        }
        for (SNode* adjacentNode : adjacentNodes)
        {
            if (!adjacentNode->visited)
            {
                adjacentNode->parent  = node;
                adjacentNode->weight  =
                    node->weight + graph->GetEdgeWeight (node, adjacentNode);
                adjacentNode->visited = true;

                if (adjacentNode == goal)
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

Nodes GraphSearchAlgorithms::Dijkstra (
    CGraph* const graph,
    SNode* const  start,
    SNode* const  goal)
{
    Nodes unfinishedNodes;
    for (SNode* node : graph->GetNodes ())
    {
        node->parent  = nullptr;
        node->weight  = std::numeric_limits<float>::infinity ();
        node->visited = false;
        unfinishedNodes.push_back (node);
    }
    start->weight  = 0.0f;
    start->visited = true;

    if (start == goal) return Nodes{ start };

    while (unfinishedNodes.size () > 0)
    {
        SNode* node = GetClosestnode (unfinishedNodes);
        unfinishedNodes.erase (
            std::remove (
                unfinishedNodes.begin ()
                , unfinishedNodes.end ()
                , node)
            , unfinishedNodes.end ());

        if (node == goal) return GetPathToSource (node);

        for (SNode* adjacentNode : graph->GetAdjacentNodes (node))
        {
            if (adjacentNode->weight >
                (node->weight + graph->GetEdgeWeight (node, adjacentNode)))
            {
                adjacentNode->weight  =
                    node->weight + graph->GetEdgeWeight (node, adjacentNode);
                adjacentNode->parent  = node;
                adjacentNode->visited = true;
            }
        }
    }
    return Nodes{};
}

Nodes GraphSearchAlgorithms::GetPathToSource (SNode* start)
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