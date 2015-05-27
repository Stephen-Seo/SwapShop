
#ifndef PLAYER_HPP
#define PLAYER_HPP

#define TIME_PER_FRAME 0.3f

#include <swapShop/SwapEntity.hpp>

class Player: public SwapEntity
{
public:
    Player(const sf::Texture& texture);

private:
    enum Direction
    {
        UP, DOWN, LEFT, RIGHT
    };

    Direction direction;
    /**
     * 0000 - nothing
     * 0001 - up pressed
     * 0010 - down pressed
     * 0100 - left pressed
     * 1000 - right pressed
     * other 4 bits unused
    **/
    unsigned char dirByte;
    bool currentStep;
    float currentTime;
    bool stationary;

    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

