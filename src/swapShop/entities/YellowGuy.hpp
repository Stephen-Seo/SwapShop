
#ifndef YELLOWGUY_HPP
#define YELLOWGUY_HPP

#include <swapShop/SwapEntity.hpp>

class YellowGuy : public SwapEntity
{
public:
    YellowGuy(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif

