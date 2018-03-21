#pragma once

#include "Types.h"

class CGrid;

namespace GridSearchAlgorithms
{
    // Applies Breadth First Search algorithm and returns a path to the goal.
    // If the goal cannot be reached, returns an empty path.
    Nodes BreadthFirstSearch (
        CGrid* const grid,
        const int    start,
        const int    goal = -1);
    // Applies Depth First Search algorithm and returns a path to the goal. If
    // the goal cannot be reached, returns an empty path.
    Nodes DepthFirstSearch (
        CGrid* const grid,
        const int    start,
        const int    goal = -1,
        const bool   searchFromRight = false);
    // Applies Dijkstra algorithm and returns a path to the goal. If the goal
    // cannot be reached, returns an empty path.
    Nodes Dijkstra (
        CGrid* const grid,
        const int    start,
        const int    goal = -1);

    // Returns the node with the lowest weight in the vector passed.
    SNode* GetClosestnode (const Nodes vector, const WeightVector weights);

    Nodes GetPathToSource (SNode* start);
}