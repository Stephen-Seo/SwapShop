
#include <swapShop/entities/Potion.hpp>

Potion::Potion(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(7*16, 3*16, 0);

    hp = 1;
    maxHP = 10;
}

void Potion::updateCurrent(sf::Time dt, Context context)
{

}

void Potion::handleEventCurrent(const sf::Event& event, Context context)
{

}

void Potion::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

