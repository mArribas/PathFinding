#pragma once

#include <vector>

struct SNode;

typedef std::vector<std::vector<float>> WeightMatrix;
typedef std::vector<float>              WeightVector;
typedef std::vector<unsigned int>       AdjacencyVector;
typedef std::vector<SNode*>             Nodes;