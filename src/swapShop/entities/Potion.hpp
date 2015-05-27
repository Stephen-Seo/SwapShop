
#ifndef POTION_HPP
#define POTION_HPP

#include <swapShop/SwapEntity.hpp>

class Potion : public SwapEntity
{
public:
    Potion(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

