#include "AdjacencyMatrix.h"

#include "DebugNew.h"

CAdjacencyMatrix::CAdjacencyMatrix (const unsigned int size)
{
    mSize = size;

    // Grow rows and columns.
    mMatrix.resize (mSize);
    for (unsigned int i = 0; i < mSize; ++i)
    {
        mMatrix[i].resize (mSize);
    }

    for (unsigned int i = 0; i < mSize; ++i)
    {
        for (unsigned int j = 0; j < mSize; ++j)
        {
            mMatrix[i][j] = -1.f;
        }
    }
}

CAdjacencyMatrix::~CAdjacencyMatrix (void)
{
}

void CAdjacencyMatrix::AddDirectionalEdge (
    const unsigned int from,
    const unsigned int to,
    const float        weight)
{
    mMatrix[from][to] = weight;
}

void CAdjacencyMatrix::AddNonDirectionalEdge (
    const unsigned int v1,
    const unsigned int v2,
    const float        weight)
{
    mMatrix[v1][v2] = weight;
    mMatrix[v2][v1] = weight;
}

float CAdjacencyMatrix::GrabEdgeWeight (
    const unsigned int x,
    const unsigned int y) const
{
    return mMatrix[x][y];
}


void CAdjacencyMatrix::SetSize (const unsigned int size)
{
    mSize = size;
}

unsigned int CAdjacencyMatrix::GetSize (void) const
{
    return mSize;
}

const AdjacencyVector CAdjacencyMatrix::GetAdjacencyVector (
    const unsigned int index) const
{
    std::vector<unsigned int> adjacencyList;

    for (unsigned int i = 0; i < mSize; ++i)
    {
        if ((mMatrix[index][i] != -1.f) && (index != i))
        {
            adjacencyList.push_back (i);
        }
    }

    return adjacencyList;
}