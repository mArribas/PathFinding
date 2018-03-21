#pragma once

#include "Types.h"

class CGrid
{
public:
    CGrid (
        const unsigned int numRows,
        const unsigned int numColumns,
        const float        nodeSize);
    ~CGrid (void);

    Nodes         GetNodes         (void)            const;
    SNode*        GetNode          (const int index) const;
    Nodes         GetAdjacentNodes (const int index) const;
    float         GetWeight        (const int index) const;
    WeightVector& GetWeights       (void);

    void Draw     (void)             const;
    void DrawPath (const Nodes path) const;
private:
    static unsigned int sIndex;

    // A std vector of SNode*.
    Nodes              mNodes;
    const unsigned int mRows;
    const unsigned int mColumns;
    WeightVector       mWeights;
};