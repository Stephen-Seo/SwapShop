
#ifndef COIN_HPP
#define COIN_HPP

#include <swapShop/SwapEntity.hpp>

class Coin : public SwapEntity
{
public:
    Coin(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

