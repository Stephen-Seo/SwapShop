
#include <swapShop/entities/YellowGuy.hpp>

YellowGuy::YellowGuy(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(2*16, 2*16, 0);
    sprite.setSprite(3*16, 2*16, 1);
    sprite.setSprite(4*16, 2*16, 2);
    sprite.setSprite(5*16, 2*16, 3);
    sprite.setSprite(6*16, 2*16, 4);
    sprite.setSprite(7*16, 2*16, 5);
    sprite.setSprite(0, 3*16, 6);
    sprite.setSprite(16, 3*16, 7);
    sprite.setSprite(2*16, 3*16, 8);

    hp = 3;
    maxHP = 3;
}

void YellowGuy::updateCurrent(sf::Time dt, Context context)
{

}

void YellowGuy::handleEventCurrent(const sf::Event& event, Context context)
{

}

void YellowGuy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

