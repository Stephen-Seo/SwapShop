
#ifndef REDGUY_HPP
#define REDGUY_HPP

#include <swapShop/SwapEntity.hpp>

class RedGuy : public SwapEntity
{
public:
    RedGuy(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif
