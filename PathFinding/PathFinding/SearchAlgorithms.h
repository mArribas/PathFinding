#pragma once

#include "Types.h"

class CGraph;

namespace SearchAlgorithms
{
    // Breadth First Search.
    void     BFS     (CGraph* const graph, SVertex* const start);
    // Breadth First Search with goal.
    Vertices GoalBFS (
        CGraph* const  graph,
        SVertex* const start,
        SVertex* const goal);

    // Depth First Search.
    void     DFS     (
        CGraph* const  graph,
        SVertex* const start,
        const bool     searchFromRight = false);
    // Depth First Search with goal.
    Vertices GoalDFS (
        CGraph* const  graph,
        SVertex* const start,
        SVertex* const goal,
        const bool     searchFromRight = false);

    void     Dijkstra     (CGraph* const graph, SVertex* const start);
    Vertices GoalDijkstra (
        CGraph* const  graph,
        SVertex* const start,
        SVertex* const goal);

    SVertex* GetClosestVertex (const Vertices vector);

    Vertices GetPathToSource (SVertex* start);
}