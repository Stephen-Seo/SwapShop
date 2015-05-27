
#include <swapShop/entities/BlueBricks.hpp>

BlueBricks::BlueBricks(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(0, 6*16, 0);
    sprite.setSprite(16, 6*16, 1);
    sprite.setSprite(2*16, 6*16, 2);
    sprite.setSprite(3*16, 6*16, 3);
}

void BlueBricks::updateCurrent(sf::Time dt, Context context)
{

}

void BlueBricks::handleEventCurrent(const sf::Event& event, Context context)
{

}

void BlueBricks::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

