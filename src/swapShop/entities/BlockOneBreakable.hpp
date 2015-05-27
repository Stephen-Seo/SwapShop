
#ifndef BLOCK_ONE_BREAKABLE_HPP
#define BLOCK_ONE_BREAKABLE_HPP

#include <swapShop/SwapEntity.hpp>

class BlockOneBreakable : public SwapEntity
{
public:
    BlockOneBreakable(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

