
#ifndef BLOCK_ZERO_BREAKABLE_HPP
#define BLOCK_ZERO_BREAKABLE_HPP

#include <swapShop/SwapEntity.hpp>

class BlockZeroBreakable : public SwapEntity
{
public:
    BlockZeroBreakable(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

