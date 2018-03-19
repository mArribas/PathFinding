#pragma once

#include "Types.h"

class CAdjacencyMatrix;

class CGraph
{
public:
    CGraph  (const Vertices vertices);
    ~CGraph (void);

    void  CreateDirectionalEdge    (
        const unsigned int from,
        const unsigned int to,
        const float        weight = 1.f);
    void  CreateDirectionalEdge    (
        const SVertex* const from,
        const SVertex* const to,
        const float          weight = 1.f);
    void  CreateNonDirectionalEdge (
        const unsigned int v1,
        const unsigned int v2,
        const float        weight = 1.f);
    void  CreateNonDirectionalEdge (
        const SVertex* const v1,
        const SVertex* const v2,
        const float          weight = 1.f);

    float    GetEdgeWeight       (
        const SVertex* to,
        const SVertex* from) const;
    Vertices GetVertices         (void) const;
    Vertices GetAdjacentVertices (const unsigned int index) const;
    Vertices GetAdjacentVertices (const SVertex* const vertex) const;

    void Draw (void) const;
private:
    static unsigned int sIndex;

    // A std vector of SVertex*.
    Vertices          mVertices;
    CAdjacencyMatrix* mAdjacencyMatrix;
};