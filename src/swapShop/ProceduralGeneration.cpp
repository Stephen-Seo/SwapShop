
#include <swapShop/ProceduralGeneration.hpp>

#include <random>

std::unordered_set<Coordinate<int> > ProceduralGeneration::drunkardWalk(int maxX, int maxY, bool randomStart, int startX, int startY)
{
    std::random_device rd;
    return ProceduralGeneration::drunkardWalk(maxX, maxY, rd(), randomStart, startX, startY);
}

std::unordered_set<Coordinate<int> > ProceduralGeneration::drunkardWalk(int maxX, int maxY, unsigned int seed, bool randomStart, int startX, int startY)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0, 3);

    std::unordered_set<Coordinate<int> > set;
    Coordinate<int> current;

    if(randomStart)
    {
        std::uniform_int_distribution<> startDisX(0, maxX);
        std::uniform_int_distribution<> startDisY(0, maxY);

        current.x = startDisX(gen);
        current.y = startDisY(gen);
        set.insert(current);
    }
    else
    {
        current.x = startX;
        current.y = startY;
        set.insert(current);
    }

    // 0 - up
    // 1 - down
    // 2 - left
    // 3 - right

    // TODO

    return set;
}
