
#include <swapShop/entities/GreenBricks.hpp>

GreenBricks::GreenBricks(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(4*16, 6*16, 0);
    sprite.setSprite(5*16, 6*16, 1);
    sprite.setSprite(6*16, 6*16, 2);
    sprite.setSprite(7*16, 6*16, 3);
}

void GreenBricks::updateCurrent(sf::Time dt, Context context)
{

}

void GreenBricks::handleEventCurrent(const sf::Event& event, Context context)
{

}

void GreenBricks::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

