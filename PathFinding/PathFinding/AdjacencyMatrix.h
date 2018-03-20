#pragma once

#include "Types.h"

// A matrix that contains the weight of the edge if the Nodes are adjacent,
// and -1 if not.
class CAdjacencyMatrix
{
public:
    CAdjacencyMatrix  (const unsigned int size);
    ~CAdjacencyMatrix (void);

    void  AddDirectionalEdge    (
        const unsigned int from,
        const unsigned int to,
        const float weight);
    void  AddNonDirectionalEdge (
        const unsigned int v1,
        const unsigned int v2,
        const float weight);
    float GrabEdgeWeight        (
        const unsigned int x,
        const unsigned int y) const;

    void         SetSize (const unsigned int size);
    unsigned int GetSize (void) const;

    const AdjacencyVector GetAdjacencyVector (const unsigned int index) const;
private:
    WeightMatrix mMatrix;
    unsigned int mSize;
};