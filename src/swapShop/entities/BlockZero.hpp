
#ifndef BLOCK_ZERO_HPP
#define BLOCK_ZERO_HPP

#include <swapShop/SwapEntity.hpp>

class BlockZero : public SwapEntity
{
public:
    BlockZero(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

