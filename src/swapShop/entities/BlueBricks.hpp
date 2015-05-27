
#ifndef BLUE_BRICKS_BREAKABLE_HPP
#define BLUE_BRICKS_BREAKABLE_HPP

#include <swapShop/SwapEntity.hpp>

class BlueBricks : public SwapEntity
{
public:
    BlueBricks(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

