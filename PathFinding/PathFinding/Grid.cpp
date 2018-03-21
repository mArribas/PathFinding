#include "Grid.h"

#include "DebugNew.h"
#include "Node.h"

#include <cassert>

unsigned int CGrid::sIndex = 0;

CGrid::CGrid (
    const unsigned int numRows,
    const unsigned int numColumns,
    const float        nodeSize)
    : mRows   {numRows}
    , mColumns{numColumns}
{
    const unsigned int totalNodes = mRows * mColumns;
    const float        halfSize   = nodeSize / 2.f;
    float nextPosX{ halfSize };
    float nextPosY{ halfSize };

    for (unsigned int i = 0; i < totalNodes; ++i)
    {
        SNode* newNode{ new SNode{} };
        mNodes.push_back (newNode);

        newNode->index       = sIndex++;
        newNode->size        = nodeSize;
        newNode->weight      = 1.f;
        newNode->position.mX = nextPosX;
        newNode->position.mY = nextPosY;

        if ((i + 1) % mColumns == 0)
        {
            nextPosX  = halfSize;
            nextPosY += nodeSize;
        }
        else
        {
            nextPosX += nodeSize;
        }

        mWeights.push_back (0.f);
    }
}

CGrid::~CGrid (void)
{
    for (const auto& node : mNodes)
    {
        delete node;
    }
    mNodes.clear ();
}

Nodes CGrid::GetNodes (void) const
{
    return mNodes;
}

SNode* CGrid::GetNode (const int index) const
{
    assert ((index >= 0) && (index < static_cast<int>(mRows * mColumns)));

    return mNodes[index];
}

Nodes CGrid::GetAdjacentNodes (const int index) const
{
    assert ((index >= 0) && (index < static_cast<int>(mRows * mColumns)));

    Nodes              nodes;
    const int up    = (index / mColumns) - 1;
    const int down  = (index / mColumns) + 1;
    const int right = (index % mColumns) + 1;
    const int left  = (index % mColumns) - 1;

    if ((up >= 0) && (up < static_cast<int>(mRows)))
    {
        nodes.push_back (mNodes[index - mColumns]);
    }

    if ((down >= 0) && (down < static_cast<int>(mRows)))
    {
        nodes.push_back (mNodes[index + mColumns]);
    }

    if ((right >= 0) && (right < static_cast<int>(mColumns)))
    {
        nodes.push_back (mNodes[index + 1]);
    }

    if ((left >= 0) && (left < static_cast<int>(mColumns)))
    {
        nodes.push_back (mNodes[index - 1]);
    }

    return nodes;
}
float CGrid::GetWeight (const int index) const
{
    assert ((index >= 0) && (index < static_cast<int>(mRows * mColumns)));

    return mWeights[index];
}

WeightVector& CGrid::GetWeights (void)
{
    return mWeights;
}

void CGrid::Draw (void) const
{
    for (SNode* node : mNodes)
    {
#pragma warning(push)
#pragma warning(disable: 4244)

        if (node->visited)
        {
            DrawRectangle (
                node->position.mX - node->size / 2
                , node->position.mY - node->size / 2
                , node->size
                , node->size
                , SKYBLUE);
        }
        DrawRectangleLines (
            node->position.mX - node->size / 2
            , node->position.mY - node->size / 2
            , node->size
            , node->size
            , BLACK);
        DrawText (
            std::to_string (static_cast<int>(node->weight)).c_str ()
            , node->position.mX - node->size / 2.5f
            , node->position.mY - node->size / 2.5f
            , node->size * 0.33f
            , BLACK);
        if (!node->visited)
        {
            DrawText (
                "-"
                , node->position.mX - node->size / 2.5f
                , node->position.mY + node->size / 5.f
                , node->size * 0.33f
                , RED);
        }
        else
        {
            DrawText (
                std::to_string (static_cast<int>(mWeights[node->index])).c_str ()
                , node->position.mX - node->size / 2.5f
                , node->position.mY + node->size / 5.f
                , node->size * 0.33f
                , RED);
        }

#pragma warning(pop)
    }
}

void CGrid::DrawPath (const Nodes path) const
{
    if (path.empty ()) return;

    for (SNode* node : path)
    {
#pragma warning(push)
#pragma warning(disable: 4244)

        DrawRectangle (
            node->position.mX - node->size / 2
            , node->position.mY - node->size / 2
            , node->size
            , node->size
            , GREEN);
        DrawRectangleLines (
            node->position.mX - node->size / 2
            , node->position.mY - node->size / 2
            , node->size
            , node->size
            , BLACK);
        DrawText (
            std::to_string (static_cast<int>(node->weight)).c_str ()
            , node->position.mX - node->size / 2.5f
            , node->position.mY - node->size / 2.5f
            , node->size * 0.33f
            , BLACK);
        DrawText (
            std::to_string (static_cast<int>(mWeights[node->index])).c_str ()
            , node->position.mX - node->size / 2.5f
            , node->position.mY + node->size / 5.f
            , node->size * 0.33f
            , RED);

#pragma warning(pop)
    }
}