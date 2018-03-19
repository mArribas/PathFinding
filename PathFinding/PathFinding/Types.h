#pragma once

#include <vector>

struct SVertex;

typedef std::vector<std::vector<float>> WeightMatrix;
typedef std::vector<unsigned int>       AdjacencyVector;
typedef std::vector<SVertex*>           Vertices;