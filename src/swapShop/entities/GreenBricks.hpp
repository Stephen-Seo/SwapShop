
#ifndef GREEN_BRICKS_BREAKABLE_HPP
#define GREEN_BRICKS_BREAKABLE_HPP

#include <swapShop/SwapEntity.hpp>

class GreenBricks : public SwapEntity
{
public:
    GreenBricks(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

