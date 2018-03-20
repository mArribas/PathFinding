#pragma once

#include "Types.h"

class CGraph;

namespace SearchAlgorithms
{
    // Breadth First Search.
    void  BFS     (CGraph* const graph, SNode* const start);
    // Breadth First Search with goal.
    Nodes GoalBFS (CGraph* const graph, SNode* const start, SNode* const goal);
    //void  StepBFS (CGraph* const graph, SNode* const start, SNode* const goal);

    // Depth First Search.
    void  DFS     (
        CGraph* const graph,
        SNode* const  start,
        const bool    searchFromRight = false);
    // Depth First Search with goal.
    Nodes GoalDFS (
        CGraph* const graph,
        SNode* const  start,
        SNode* const  goal,
        const bool    searchFromRight = false);

    void  Dijkstra     (CGraph* const graph, SNode* const start);
    Nodes GoalDijkstra (
        CGraph* const graph,
        SNode* const  start,
        SNode* const  goal);

    SNode* GetClosestnode (const Nodes vector);

    Nodes GetPathToSource (SNode* start);
}