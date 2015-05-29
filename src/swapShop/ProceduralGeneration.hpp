
#ifndef PROCEDURAL_GENERATION_HPP
#define PROCEDURAL_GENERATION_HPP

#include <unordered_set>

#include <swapShop/Coordinate.hpp>

namespace ProceduralGeneration
{
    std::unordered_set<Coordinate<int> > drunkardWalk(int maxX, int maxY, bool randomStart = true, int startX = 0, int startY = 0);
    std::unordered_set<Coordinate<int> > drunkardWalk(int maxX, int maxY, unsigned int seed, bool randomStart = true, int startX = 0, int startY = 0);
}

#endif

