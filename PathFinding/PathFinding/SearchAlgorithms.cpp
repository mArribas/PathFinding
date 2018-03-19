#include "SearchAlgorithms.h"

#include "DebugNew.h"
#include "Vertex.h"
#include "Graph.h"

#include <queue>
#include <algorithm>
#include <limits>

void SearchAlgorithms::BFS (CGraph* const graph, SVertex* const start)
{
    for (SVertex* vertex : graph->GetVertices ())
    {
        vertex->parent  = nullptr;
        vertex->weight  = 0.0f;
        vertex->visited =false;
    }

    std::queue<SVertex*> queue;
    queue.push (start);

    while (queue.size () > 0)
    {
        SVertex* vertex = queue.front ();
        queue.pop ();

        for (SVertex* neighbour : graph->GetAdjacentVertices (vertex))
        {
            if (neighbour->visited == false)
            {
                neighbour->parent  = vertex;
                neighbour->weight  =
                    vertex->weight + graph->GetEdgeWeight (vertex, neighbour);
                neighbour->visited = true;

                queue.push (neighbour);
            }
        }
        vertex->visited = true;
    }
}

Vertices SearchAlgorithms::GoalBFS (
    CGraph* const  graph,
    SVertex* const start,
    SVertex* const goal)
{
    if (start == goal)
    {
        return Vertices{ start };
    }
    for (SVertex* vertex : graph->GetVertices ())
    {
        vertex->parent  = nullptr;
        vertex->weight  = 0.0f;
        vertex->visited = false;
    }

    std::queue<SVertex*> queue;
    queue.push (start);

    while (queue.size () > 0)
    {
        SVertex* vertex = queue.front ();
        queue.pop ();

        for (SVertex* neighbour : graph->GetAdjacentVertices (vertex))
        {
            if (neighbour->visited == false)
            {
                neighbour->parent  = vertex;
                neighbour->weight  =
                    vertex->weight + graph->GetEdgeWeight (vertex, neighbour);
                neighbour->visited = true;

                if (neighbour == goal)
                {
                    return GetPathToSource (neighbour);
                }

                queue.push (neighbour);
            }
        }
        vertex->visited = true;
    }

    // No path to goal vertex exists.
    return Vertices{};
}

void SearchAlgorithms::DFS (
    CGraph* const  graph,
    SVertex* const start,
    const bool     searchFromRight)
{
    for (SVertex* vertex : graph->GetVertices ())
    {
        vertex->parent  = nullptr;
        vertex->weight  = 0.0f;
        vertex->visited = false;
    }

    std::vector<SVertex*> stack;
    stack.push_back (start);

    while (stack.size () > 0)
    {
        SVertex* vertex = stack.back ();
        stack.pop_back ();

        Vertices neighbours = graph->GetAdjacentVertices (vertex);
        if (searchFromRight == true)
        {
            std::reverse (neighbours.begin (), neighbours.end ());
        }
        for (SVertex* neighbour : neighbours)
        {
            if (neighbour->visited == false)
            {
                neighbour->parent  = vertex;
                neighbour->weight  =
                    vertex->weight + graph->GetEdgeWeight (vertex, neighbour);
                neighbour->visited = true;

                stack.push_back (neighbour);
            }
        }
        vertex->visited = true;
    }
}

Vertices SearchAlgorithms::GoalDFS (
    CGraph* const  graph,
    SVertex* const start,
    SVertex* const goal,
    const bool     searchFromRight)
{
    if (start == goal)
    {
        return Vertices{ start };
    }
    for (SVertex* vertex : graph->GetVertices ())
    {
        vertex->parent  = nullptr;
        vertex->weight  = 0.0f;
        vertex->visited = false;
    }

    Vertices stack;
    stack.push_back (start);

    while (stack.size () > 0)
    {
        SVertex* vertex = stack.back ();
        stack.pop_back ();

        Vertices neighbours = graph->GetAdjacentVertices (vertex);
        if (searchFromRight == true)
        {
            std::reverse (neighbours.begin (), neighbours.end ());
        }
        for (SVertex* neighbour : neighbours)
        {
            if (neighbour->visited == false)
            {
                neighbour->parent = vertex;
                neighbour->weight =
                    vertex->weight + graph->GetEdgeWeight (vertex, neighbour);
                neighbour->visited = true;

                if (neighbour == goal)
                {
                    return GetPathToSource (neighbour);
                }

                stack.push_back (neighbour);
            }
        }
        vertex->visited = true;
    }

    // No path to goal vertex exists.
    return Vertices{};
}

void SearchAlgorithms::Dijkstra (
    CGraph* const  graph,
    SVertex* const start)
{
    Vertices unfinishedVertices;
    for (SVertex* vertex : graph->GetVertices ())
    {
        vertex->parent = nullptr;
        vertex->weight = std::numeric_limits<float>::infinity ();
        unfinishedVertices.push_back (vertex);
    }
    start->weight = 0.0f;

    while (unfinishedVertices.size () > 0)
    {
        SVertex* vertex = GetClosestVertex (unfinishedVertices);
        unfinishedVertices.erase (
            std::remove (
                unfinishedVertices.begin ()
                ,unfinishedVertices.end ()
                , vertex)
            , unfinishedVertices.end ());

        for (SVertex* adjVertex : graph->GetAdjacentVertices (vertex))
        {
            if (adjVertex->weight >
                (vertex->weight + graph->GetEdgeWeight (vertex, adjVertex)))
            {
                adjVertex->weight =
                    vertex->weight +
                    graph->GetEdgeWeight (vertex, adjVertex);
                adjVertex->parent = vertex;
            }
        }
    }
}

Vertices SearchAlgorithms::GoalDijkstra (
    CGraph* const  graph,
    SVertex* const start,
    SVertex* const goal)
{
    if (start == goal)
    {
        return Vertices{ start };
    }
    Vertices unfinishedVertices;
    for (SVertex* vertex : graph->GetVertices ())
    {
        vertex->parent = nullptr;
        vertex->weight = std::numeric_limits<float>::infinity ();
        unfinishedVertices.push_back (vertex);
    }
    start->weight = 0.0f;

    while (unfinishedVertices.size () > 0)
    {
        SVertex* vertex = GetClosestVertex (unfinishedVertices);
        unfinishedVertices.erase (
            std::remove (
                unfinishedVertices.begin ()
                , unfinishedVertices.end ()
                , vertex)
            , unfinishedVertices.end ());

        if (vertex == goal) return GetPathToSource (vertex);

        for (SVertex* adjVertex : graph->GetAdjacentVertices (vertex))
        {
            if (adjVertex->weight >
                (vertex->weight + graph->GetEdgeWeight (vertex, adjVertex)))
            {
                adjVertex->weight = 
                    vertex->weight + graph->GetEdgeWeight (vertex, adjVertex);
                adjVertex->parent = vertex;
            }
        }
    }
    return Vertices{};
}

SVertex* SearchAlgorithms::GetClosestVertex (const Vertices vector)
{
    SVertex* candidate = vector[0];

    for (SVertex* vertex : vector)
    {
        if (vertex->weight < candidate->weight) candidate = vertex;

    }

    return candidate;
}

Vertices SearchAlgorithms::GetPathToSource (SVertex* start)
{
    Vertices path;
    SVertex* next = start;

    while (next != nullptr)
    {
        path.push_back (next);
        next = next->parent;
    }

    return path;
}