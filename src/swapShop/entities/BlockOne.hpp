
#ifndef BLOCK_ONE_HPP
#define BLOCK_ONE_HPP

#include <swapShop/SwapEntity.hpp>

class BlockOne : public SwapEntity
{
public:
    BlockOne(const sf::Texture& texture);

private:
    virtual void updateCurrent(sf::Time dt, Context context);
    virtual void handleEventCurrent(const sf::Event& event, Context context);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

