
#include <swapShop/entities/Player.hpp>

Player::Player(const sf::Texture& texture) :
SwapEntity(texture),
direction(DOWN),
dirByte(0),
currentStep(true),
stationary(true)
{
    sprite.setSprite(0, 0, 0);
    sprite.setSprite(16, 0, 1);
    sprite.setSprite(2*16, 0, 2);
    sprite.setSprite(3*16, 0, 3);
    sprite.setSprite(4*16, 0, 4);
    sprite.setSprite(5*16, 0, 5);
    sprite.setSprite(6*16, 0, 6);
    sprite.setSprite(7*16, 0, 7);
    sprite.setSprite(0, 16, 8);

    hp = 10;
    maxHP = 10;
}

void Player::updateCurrent(sf::Time dt, Context context)
{
    currentTime += dt.asSeconds();

    if(currentTime >= TIME_PER_FRAME)
    {
        currentStep = !currentStep;
        currentTime = 0.0f;
    }

    if(direction == LEFT)
    {
        sprite.flipHorizontal(true);
    }
    else
    {
        sprite.flipHorizontal(false);
    }

    if(stationary)
    {
        switch(direction)
        {
        case UP:
            sprite.displaySprite(6);
            break;
        case DOWN:
            sprite.displaySprite(0);
            break;
        case LEFT:
        case RIGHT:
            sprite.displaySprite(3);
            break;
        }
    }
    else
    {
        switch(direction)
        {
        case UP:
            sprite.displaySprite(7 + (currentStep ? 0 : 1));
            break;
        case DOWN:
            sprite.displaySprite(1 + (currentStep ? 0 : 1));
            break;
        case LEFT:
        case RIGHT:
            sprite.displaySprite(4 + (currentStep ? 0 : 1));
            break;
        }
    }

    sprite.update(dt);
}

void Player::handleEventCurrent(const sf::Event& event, Context context)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::W)
        {
            direction = UP;
            dirByte |= 0x1;
        }
        else if(event.key.code == sf::Keyboard::S)
        {
            direction = DOWN;
            dirByte |= 0x2;
        }

        if(event.key.code == sf::Keyboard::A)
        {
            direction = LEFT;
            dirByte |= 0x4;
        }
        else if(event.key.code == sf::Keyboard::D)
        {
            direction = RIGHT;
            dirByte |= 0x8;
        }
    }

    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::W)
        {
            dirByte &= 0xE;
        }
        else if(event.key.code == sf::Keyboard::S)
        {
            dirByte &= 0xD;
        }

        if(event.key.code == sf::Keyboard::A)
        {
            dirByte &= 0xB;
        }
        else if(event.key.code == sf::Keyboard::D)
        {
            dirByte &= 0x7;
        }
    }

    stationary = (dirByte == 0);
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}
