#include "Graph.h"

#include "DebugNew.h"
#include "Vertex.h"
#include "AdjacencyMatrix.h"

#define TORAD(x) (x * (PI / 180.f))

unsigned int CGraph::sIndex = 0;

CGraph::CGraph (const Vertices vertices) : mVertices{ vertices }
{
    mAdjacencyMatrix = new CAdjacencyMatrix{ mVertices.size () };

    for (auto& vertex : mVertices)
    {
        vertex->index = sIndex++;
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
    const SVertex* const from,
    const SVertex* const to,
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
    const SVertex* const v1,
    const SVertex* const v2,
    const float          weight)
{
    CreateNonDirectionalEdge (v1->index, v2->index, weight);
}

float CGraph::GetEdgeWeight (
    const SVertex* const v1,
    const SVertex* const v2) const
{
    return mAdjacencyMatrix->GrabEdgeWeight (v1->index, v2->index);
}

Vertices CGraph::GetVertices (void) const
{
    return mVertices;
}

Vertices CGraph::GetAdjacentVertices (const unsigned int index) const
{
    const AdjacencyVector adjacentIndices{
        mAdjacencyMatrix->GetAdjacencyVector (index) };
    Vertices              adjacentVertices;

    for (unsigned int vertexIndex : adjacentIndices)
    {
        adjacentVertices.push_back (mVertices[vertexIndex]);
    }

    return adjacentVertices;
}

Vertices CGraph::GetAdjacentVertices (const SVertex* const vertex) const
{
    return GetAdjacentVertices (vertex->index);
}

void CGraph::Draw (void) const
{
    for (SVertex* vertex : mVertices)
    {
        Vertices adjacentVertices{ GetAdjacentVertices (vertex) };

        vertex->Draw ();

        if (adjacentVertices.empty ()) continue;

        for (SVertex* adjVertex : adjacentVertices)
        {
#pragma warning(push)
#pragma warning(disable: 4244)

            CVector2D dir   { vertex->position - adjVertex->position };
            float     length{ dir.Length () };

            dir.Normalize ();
            dir *= adjVertex->radius * 1.5f;

            DrawLine (
                vertex->position.mX
                , vertex->position.mY
                , adjVertex->position.mX
                , adjVertex->position.mY
                , BLACK
            );
            DrawCircle (
                adjVertex->position.mX + dir.mX
                , adjVertex->position.mY + dir.mY
                , adjVertex->radius / 2.f
                , vertex->tint);

            if (length <= 0.f) continue;

            dir.Normalize ();
            dir *= length / 2;

            DrawText (
                std::to_string (GetEdgeWeight (vertex, adjVertex)).c_str ()
                , adjVertex->position.mX + dir.mX
                , adjVertex->position.mY + dir.mY
                , 10
                , BLACK);

#pragma warning(pop)
        }
    }

}