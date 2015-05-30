
#ifndef YELLOWGUY_HPP
#define YELLOWGUY_HPP

#include <swapShop/SwapEntity.hpp>

#include <random>

#include <SFML/System.hpp>

#define YELLOW_MOVEMENT_SPEED 90.0f

#define YELLOW_WALK_TIME 0.3f

class YellowGuy : public SwapEntity
{
public:
    YellowGuy(const sf::Texture& texture);

private:
    float phaseTimer;
    int phase;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    sf::Vector2f moveDirection;

    float walkTimer;
    bool walkPhase;

    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif

