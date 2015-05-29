
#include <swapShop/ProceduralGeneration.hpp>

#include <random>

std::unordered_set<Coordinate<int> > ProceduralGeneration::drunkardWalk(int maxX, int maxY, float percentage, bool randomStart, int startX, int startY)
{
    std::random_device rd;
    return ProceduralGeneration::drunkardWalk(maxX, maxY, rd(), percentage, randomStart, startX, startY);
}

std::unordered_set<Coordinate<int> > ProceduralGeneration::drunkardWalk(int maxX, int maxY, unsigned int seed, float percentage, bool randomStart, int startX, int startY)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0, 3);

    std::unordered_set<Coordinate<int> > set;
    Coordinate<int> current;

    if(maxX <= 0 || maxY <= 0)
    {
        return set;
    }

    if(randomStart)
    {
        std::uniform_int_distribution<> startDisX(0, maxX - 1);
        std::uniform_int_distribution<> startDisY(0, maxY - 1);

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

    // down is +y and right is +x
    // 0 - up
    // 1 - down
    // 2 - left
    // 3 - right

    float cells = maxX * maxY;
    int next;
    Coordinate<int> prev = current;
    while((float) set.size() / cells < percentage)
    {
        next = dis(gen);
        switch(next)
        {
        case 0:
            --current.y;
            break;
        case 1:
            ++current.y;
            break;
        case 2:
            --current.x;
            break;
        case 3:
            ++current.x;
            break;
        }

        if(current.x >= 0 && current.x < maxX && current.y >= 0 && current.y < maxY)
        {
            // coordinate is within bounds
            if(set.find(current) == set.end())
            {
                set.insert(current);
                prev = current;
            }
        }
        else
        {
            current = prev;
        }
    }

    return set;
}

