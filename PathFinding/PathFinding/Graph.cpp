#include "Graph.h"

#include "DebugNew.h"
#include "Node.h"
#include "AdjacencyMatrix.h"

#define TORAD(x) (x * (PI / 180.f))

unsigned int CGraph::sIndex = 0;

CGraph::CGraph (const Nodes nodes) : mNodes{ nodes }
{
    mAdjacencyMatrix = new CAdjacencyMatrix{ mNodes.size () };

    for (auto& node : mNodes)
    {
        node->index = sIndex++;
    }
}

CGraph::~CGraph (void)
{
    delete mAdjacencyMatrix;
}

void CGraph::CreateDirectionalEdge (
    const unsigned int from,
    const unsigned int to,
    const float        weight)
{
    mAdjacencyMatrix->AddDirectionalEdge (from, to, weight);
}

void CGraph::CreateDirectionalEdge (
    const SNode* const from,
    const SNode* const to,
    const float          weight)
{
    CreateDirectionalEdge (from->index, to->index, weight);
}

void CGraph::CreateNonDirectionalEdge (
    const unsigned int v1,
    const unsigned int v2,
    const float        weight)
{
    mAdjacencyMatrix->AddNonDirectionalEdge (v1, v2, weight);
}

void CGraph::CreateNonDirectionalEdge (
    const SNode* const v1,
    const SNode* const v2,
    const float          weight)
{
    CreateNonDirectionalEdge (v1->index, v2->index, weight);
}

float CGraph::GetEdgeWeight (const SNode* const v1, const SNode* const v2) const
{
    return mAdjacencyMatrix->GrabEdgeWeight (v1->index, v2->index);
}

Nodes CGraph::GetNodes (void) const
{
    return mNodes;
}

Nodes CGraph::GetAdjacentNodes (const unsigned int index) const
{
    const AdjacencyVector adjacentIndices{
        mAdjacencyMatrix->GetAdjacencyVector (index) };
    Nodes                 adjacentNodes;

    for (unsigned int nodeIndex : adjacentIndices)
    {
        adjacentNodes.push_back (mNodes[nodeIndex]);
    }

    return adjacentNodes;
}

Nodes CGraph::GetAdjacentNodes (const SNode* const node) const
{
    return GetAdjacentNodes (node->index);
}

void CGraph::Draw (void) const
{
    for (SNode* node : mNodes)
    {
        Nodes adjacentNodes{ GetAdjacentNodes (node) };

        node->Draw ();

        if (adjacentNodes.empty ()) continue;

        for (SNode* adjnode : adjacentNodes)
        {
#pragma warning(push)
#pragma warning(disable: 4244)

            CVector2D dir   { node->position - adjnode->position };
            float     length{ dir.Length () };

            dir.Normalize ();
            dir *= adjnode->radius * 1.f;

            DrawLine (
                node->position.mX
                , node->position.mY
                , adjnode->position.mX
                , adjnode->position.mY
                , BLACK
            );
            DrawCircle (
                adjnode->position.mX + dir.mX
                , adjnode->position.mY + dir.mY
                , adjnode->radius / 4.f
                , node->tint);

            if (length <= 0.f) continue;

            dir.Normalize ();
            dir *= length / 2;

            DrawText (
                std::to_string (
                    static_cast<int>(GetEdgeWeight (node, adjnode))).c_str ()
                , adjnode->position.mX + dir.mX
                , adjnode->position.mY + dir.mY
                , 30
                , BLACK);

#pragma warning(pop)
        }
    }

}