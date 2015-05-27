
#include <swapShop/entities/BlockZeroBreakable.hpp>

BlockZeroBreakable::BlockZeroBreakable(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(4*16, 4*16, 0);
    sprite.setSprite(5*16, 4*16, 1);

    hp = 5;
    maxHP = 5;
}

void BlockZeroBreakable::updateCurrent(sf::Time dt, Context context)
{

}

void BlockZeroBreakable::handleEventCurrent(const sf::Event& event, Context context)
{

}

void BlockZeroBreakable::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

