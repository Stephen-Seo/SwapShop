
#include <swapShop/entities/BlockZero.hpp>

BlockZero::BlockZero(const sf::Texture& texture) :
SwapEntity(texture)
{
    sprite.setSprite(0, 4*16, 0);
}

void BlockZero::updateCurrent(sf::Time dt, Context context)
{

}

void BlockZero::handleEventCurrent(const sf::Event& event, Context context)
{

}

void BlockZero::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

