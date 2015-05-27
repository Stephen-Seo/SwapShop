
#include <swapShop/entities/Heart.hpp>

Heart::Heart(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(6*16, 3*16, 0);

    hp = 1;
    maxHP = 5;
}

void Heart::updateCurrent(sf::Time dt, Context context)
{

}

void Heart::handleEventCurrent(const sf::Event& event, Context context)
{

}

void Heart::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

