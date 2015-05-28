
#include <swapShop/entities/BlueBricks.hpp>

BlueBricks::BlueBricks(const sf::Texture& texture) :
SwapEntity(texture),
timeCounter(0.0f),
currentFrame(0)
{
    sprite.setSprite(0, 6*16, 0);
    sprite.setSprite(16, 6*16, 1);
    sprite.setSprite(2*16, 6*16, 2);
    sprite.setSprite(3*16, 6*16, 3);
}

void BlueBricks::updateCurrent(sf::Time dt, Context context)
{
    timeCounter += dt.asSeconds();
    if(timeCounter >= BLUE_BRICKS_FRAME_TIME)
    {
        timeCounter = 0.0f;
        currentFrame = (currentFrame + 1) % 4;
        sprite.displaySprite(currentFrame);
    }

    sprite.update(dt);
}

void BlueBricks::handleEventCurrent(const sf::Event& event, Context context)
{

}

void BlueBricks::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

