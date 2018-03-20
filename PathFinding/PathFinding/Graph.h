#pragma once

#include "Types.h"

class CAdjacencyMatrix;

class CGraph
{
public:
    CGraph  (const Nodes nodes);
    ~CGraph (void);

    void  CreateDirectionalEdge    (
        const unsigned int from,
        const unsigned int to,
        const float        weight = 1.f);
    void  CreateDirectionalEdge    (
        const SNode* const from,
        const SNode* const to,
        const float          weight = 1.f);
    void  CreateNonDirectionalEdge (
        const unsigned int v1,
        const unsigned int v2,
        const float        weight = 1.f);
    void  CreateNonDirectionalEdge (
        const SNode* const v1,
        const SNode* const v2,
        const float          weight = 1.f);

    float GetEdgeWeight    (const SNode* to, const SNode* from) const;
    Nodes GetNodes         (void) const;
    Nodes GetAdjacentNodes (const unsigned int index) const;
    Nodes GetAdjacentNodes (const SNode* const node) const;

    void Draw (void) const;
private:
    static unsigned int sIndex;

    // A std vector of SNode*.
    Nodes             mNodes;
    CAdjacencyMatrix* mAdjacencyMatrix;
};