
#ifndef HEART_HPP
#define HEART_HPP

#include <swapShop/SwapEntity.hpp>

class Heart : public SwapEntity
{
public:
    Heart(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

