
#include <swapShop/entities/BlockOneBreakable.hpp>

BlockOneBreakable::BlockOneBreakable(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(4*16, 5*16, 0);
    sprite.setSprite(5*16, 5*16, 1);

    hp = 10;
    maxHP = 10;
}

void BlockOneBreakable::updateCurrent(sf::Time dt, Context context)
{

}

void BlockOneBreakable::handleEventCurrent(const sf::Event& event, Context context)
{

}

void BlockOneBreakable::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

