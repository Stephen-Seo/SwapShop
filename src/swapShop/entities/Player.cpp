
#include <swapShop/entities/Player.hpp>

#include <cmath>

#include <swapShop/SwapContext.hpp>

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
    // reset movement if just in battle
    if(context.swapContext->battleStatus != SwapContext::STANDBY)
    {
        dirByte = 0;
        stationary = true;
    }

    // display management
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

    // move
    if(!stationary)
    {
        sf::Vector2f movement;
        // moving up
        if((0x1 & dirByte) != 0)
        {
            movement.y = -1.0f;
        }
        // moving down
        else if((0x2 & dirByte) != 0)
        {
            movement.y = 1.0f;
        }
        // moving left
        if((0x4 & dirByte) != 0)
        {
            movement.x = -1.0f;
        }
        // moving right
        if((0x8 & dirByte) != 0)
        {
            movement.x = 1.0f;
        }

        movement /= std::sqrt(movement.x * movement.x + movement.y * movement.y);

        movement *= PLAYER_MOVEMENT_SPEED * dt.asSeconds();

        move(movement);
    }

    // update sprite
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
    else if(event.type == sf::Event::KeyReleased)
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
    else if(event.type == sf::Event::JoystickMoved)
    {
        if(event.joystickMove.axis == sf::Joystick::PovX)
        {
            if(event.joystickMove.position == 100.0f)
            {
                direction = RIGHT;
                dirByte |= 0x8;
            }
            else if(event.joystickMove.position == -100.0f)
            {
                direction = LEFT;
                dirByte |= 0x4;
            }
            else
            {
                dirByte &= 0x3;
            }
        }
        else if(event.joystickMove.axis == sf::Joystick::PovY)
        {
            if(event.joystickMove.position == 100.0f)
            {
                direction = DOWN;
                dirByte |= 0x2;
            }
            else if(event.joystickMove.position == -100.0f)
            {
                direction = UP;
                dirByte |= 0x1;
            }
            else
            {
                dirByte &= 0xC;
            }
        }
    }

    stationary = (dirByte == 0);
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
