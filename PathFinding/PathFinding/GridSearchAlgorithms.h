#pragma once

#include "Types.h"

class CGrid;

namespace GridSearchAlgorithms
{
    enum EHeuristic
    {
        eHeuristic_Euclidean,
        eHeuristic_Manhattan
    };

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
    // Applies A star algorithm and returns a path to the goal. If the goal
    // cannot be reached, returns an empty path.
    Nodes AStar (
        CGrid* const     grid,
        const int        start,
        const int        goal,
        const EHeuristic heuristic = eHeuristic_Manhattan);

    // Applies BiDirectional A star algorithm and returns a path to the goal.
    // If the goal cannot be reached, returns an empty path.
    Nodes BiDirectionalAStar (
        CGrid* const     grid,
        const int        start,
        const int        goal,
        const EHeuristic heuristic = eHeuristic_Manhattan);
}