
#include <swapShop/entities/BlockOne.hpp>

BlockOne::BlockOne(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(0, 5*16, 0);
}

void BlockOne::updateCurrent(sf::Time dt, Context context)
{

}

void BlockOne::handleEventCurrent(const sf::Event& event, Context context)
{

}

void BlockOne::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

