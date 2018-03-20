#include "SearchAlgorithms.h"

#include "DebugNew.h"
#include "Node.h"
#include "Graph.h"

#include <queue>
#include <algorithm>
#include <limits>

void SearchAlgorithms::BFS (CGraph* const graph, SNode* const start)
{
    for (SNode* node : graph->GetNodes ())
    {
        node->parent  = nullptr;
        node->weight  = 0.0f;
        node->visited =false;
    }

    std::queue<SNode*> queue;
    queue.push (start);

    while (queue.size () > 0)
    {
        SNode* node = queue.front ();
        queue.pop ();

        for (SNode* neighbour : graph->GetAdjacentNodes (node))
        {
            if (neighbour->visited == false)
            {
                neighbour->parent  = node;
                neighbour->weight  =
                    node->weight + graph->GetEdgeWeight (node, neighbour);
                neighbour->visited = true;

                queue.push (neighbour);
            }
        }
        node->visited = true;
    }
}

Nodes SearchAlgorithms::GoalBFS (
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

    while (queue.size () > 0)
    {
        SNode* node = queue.front ();
        queue.pop ();

        for (SNode* neighbour : graph->GetAdjacentNodes (node))
        {
            if (neighbour->visited == false)
            {
                neighbour->parent  = node;
                neighbour->weight  =
                    node->weight + graph->GetEdgeWeight (node, neighbour);
                neighbour->visited = true;

                if (neighbour == goal)
                {
                    return GetPathToSource (neighbour);
                }

                queue.push (neighbour);
            }
        }
        node->visited = true;
    }

    // No path to goal node exists.
    return Nodes{};
}

void SearchAlgorithms::DFS (
    CGraph* const graph,
    SNode* const  start,
    const bool    searchFromRight)
{
    for (SNode* node : graph->GetNodes ())
    {
        node->parent  = nullptr;
        node->weight  = 0.0f;
        node->visited = false;
    }

    std::vector<SNode*> stack;
    stack.push_back (start);

    while (stack.size () > 0)
    {
        SNode* node = stack.back ();
        stack.pop_back ();

        Nodes neighbours = graph->GetAdjacentNodes (node);
        if (searchFromRight == true)
        {
            std::reverse (neighbours.begin (), neighbours.end ());
        }
        for (SNode* neighbour : neighbours)
        {
            if (neighbour->visited == false)
            {
                neighbour->parent  = node;
                neighbour->weight  =
                    node->weight + graph->GetEdgeWeight (node, neighbour);
                neighbour->visited = true;

                stack.push_back (neighbour);
            }
        }
        node->visited = true;
    }
}

Nodes SearchAlgorithms::GoalDFS (
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

    while (stack.size () > 0)
    {
        SNode* node = stack.back ();
        stack.pop_back ();

        Nodes neighbours = graph->GetAdjacentNodes (node);
        if (searchFromRight == true)
        {
            std::reverse (neighbours.begin (), neighbours.end ());
        }
        for (SNode* neighbour : neighbours)
        {
            if (neighbour->visited == false)
            {
                neighbour->parent = node;
                neighbour->weight =
                    node->weight + graph->GetEdgeWeight (node, neighbour);
                neighbour->visited = true;

                if (neighbour == goal)
                {
                    return GetPathToSource (neighbour);
                }

                stack.push_back (neighbour);
            }
        }
        node->visited = true;
    }

    // No path to goal node exists.
    return Nodes{};
}

void SearchAlgorithms::Dijkstra (CGraph* const  graph, SNode* const start)
{
    Nodes unfinishedNodes;
    for (SNode* node : graph->GetNodes ())
    {
        node->parent = nullptr;
        node->weight = std::numeric_limits<float>::infinity ();
        unfinishedNodes.push_back (node);
    }
    start->weight = 0.0f;

    while (unfinishedNodes.size () > 0)
    {
        SNode* node = GetClosestnode (unfinishedNodes);
        unfinishedNodes.erase (
            std::remove (
                unfinishedNodes.begin ()
                ,unfinishedNodes.end ()
                , node)
            , unfinishedNodes.end ());

        for (SNode* adjnode : graph->GetAdjacentNodes (node))
        {
            if (adjnode->weight >
                (node->weight + graph->GetEdgeWeight (node, adjnode)))
            {
                adjnode->weight =
                    node->weight +
                    graph->GetEdgeWeight (node, adjnode);
                adjnode->parent = node;
            }
        }
    }
}

Nodes SearchAlgorithms::GoalDijkstra (
    CGraph* const graph,
    SNode* const  start,
    SNode* const  goal)
{
    Nodes unfinishedNodes;
    for (SNode* node : graph->GetNodes ())
    {
        node->parent = nullptr;
        node->weight = std::numeric_limits<float>::infinity ();
        unfinishedNodes.push_back (node);
    }
    start->weight = 0.0f;

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

        for (SNode* adjnode : graph->GetAdjacentNodes (node))
        {
            if (adjnode->weight >
                (node->weight + graph->GetEdgeWeight (node, adjnode)))
            {
                adjnode->weight = 
                    node->weight + graph->GetEdgeWeight (node, adjnode);
                adjnode->parent = node;
            }
        }
    }
    return Nodes{};
}

SNode* SearchAlgorithms::GetClosestnode (const Nodes vector)
{
    SNode* candidate = vector[0];

    for (SNode* node : vector)
    {
        if (node->weight < candidate->weight) candidate = node;
    }

    return candidate;
}

Nodes SearchAlgorithms::GetPathToSource (SNode* start)
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