#pragma once

#include "Types.h"

class CGraph;

namespace GraphSearchAlgorithms
{
    // Applies Breadth First Search algorithm and returns a path to the goal.
    // If the goal cannot be reached, returns an empty path.
    Nodes BreadthFirstSearch (
        CGraph* const graph,
        SNode* const  start,
        SNode* const  goal = nullptr);
    // Applies Depth First Search algorithm and returns a path to the goal. If
    // the goal cannot be reached, returns an empty path.
    Nodes DepthFirstSearch   (
        CGraph* const graph,
        SNode* const  start,
        SNode* const  goal            = nullptr,
        const bool    searchFromRight = false);
    // Applies Dijkstra algorithm and returns a path to the goal. If the goal
    // cannot be reached, returns an empty path.
    Nodes Dijkstra           (
        CGraph* const graph,
        SNode* const  start,
        SNode* const  goal = nullptr);

    Nodes GetPathToSource (SNode* start);
}