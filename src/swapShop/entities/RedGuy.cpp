
#include <swapShop/entities/RedGuy.hpp>

RedGuy::RedGuy(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(16, 16, 0);
    sprite.setSprite(2*16, 16, 1);
    sprite.setSprite(3*16, 16, 2);
    sprite.setSprite(4*16, 16, 3);
    sprite.setSprite(5*16, 16, 4);
    sprite.setSprite(6*16, 16, 5);
    sprite.setSprite(7*16, 16, 6);
    sprite.setSprite(0, 2*16, 7);
    sprite.setSprite(16, 2*16, 8);

    hp = 5;
    maxHP = 5;
}

void RedGuy::updateCurrent(sf::Time dt, Context context)
{

}

void RedGuy::handleEventCurrent(const sf::Event& event, Context context)
{

}

void RedGuy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}
