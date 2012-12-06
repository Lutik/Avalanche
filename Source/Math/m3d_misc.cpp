
#include "stdafx.h"
#include "math3d.h"
#include <random>

static std::mt19937 rng(98934);

float randf()
{ 
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    return dist(rng);
}