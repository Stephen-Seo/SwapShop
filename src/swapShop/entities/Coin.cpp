
#include <swapShop/entities/Coin.hpp>

Coin::Coin(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(5*16, 3*16, 0);

    hp = 1;
    maxHP = 1;
}

void Coin::updateCurrent(sf::Time dt, Context context)
{

}

void Coin::handleEventCurrent(const sf::Event& event, Context context)
{

}

void Coin::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}
