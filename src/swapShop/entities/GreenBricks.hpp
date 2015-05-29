
#ifndef GREEN_BRICKS_BREAKABLE_HPP
#define GREEN_BRICKS_BREAKABLE_HPP

#define GREEN_BRICKS_FRAME_TIME 0.35f

#include <swapShop/SwapEntity.hpp>

class GreenBricks : public SwapEntity
{
public:
    GreenBricks(const sf::Texture& texture);

private:
    float timeCounter;
    int currentFrame;

    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

