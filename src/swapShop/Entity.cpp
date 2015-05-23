
#include <swapShop/Entity.hpp>

Entity::Entity(const sf::Texture& texture, Type type) :
sprite(texture),
hp(1),
maxHP(1),
type(type)
{
    sprite.setSpriteSize(16, 16);

    switch(type)
    {
    case PLAYER:
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
        break;
    case RED_GUY:
        sprite.setSprite(16, 16, 0);
        sprite.setSprite(2*16, 16, 1);
        sprite.setSprite(3*16, 16, 2);
        sprite.setSprite(4*16, 16, 3);
        sprite.setSprite(5*16, 16, 4);
        sprite.setSprite(6*16, 16, 5);
        sprite.setSprite(7*16, 16, 6);
        sprite.setSprite(0, 2*16, 7);
        sprite.setSprite(16, 2*16, 8);

        hp = 5;
        maxHP = 5;
        break;
    case YELLOW_GUY:
        sprite.setSprite(2*16, 2*16, 0);
        sprite.setSprite(3*16, 2*16, 1);
        sprite.setSprite(4*16, 2*16, 2);
        sprite.setSprite(5*16, 2*16, 3);
        sprite.setSprite(6*16, 2*16, 4);
        sprite.setSprite(7*16, 2*16, 5);
        sprite.setSprite(0, 3*16, 6);
        sprite.setSprite(16, 3*16, 7);
        sprite.setSprite(2*16, 3*16, 8);

        hp = 3;
        maxHP = 3;
        break;
    case COIN:
        sprite.setSprite(5*16, 3*16, 0);

        hp = 1;
        maxHP = 1;
        break;
    case HEART:
        sprite.setSprite(6*16, 3*16, 0);

        hp = 1;
        maxHP = 5;
        break;
    case POTION:
        sprite.setSprite(7*16, 3*16, 0);

        hp = 1;
        maxHP = 10;
        break;
    case BLOCK_0:
        sprite.setSprite(0, 4*16, 0);
        break;
    case BLOCK_1:
        sprite.setSprite(0, 5*16, 0);
        break;
    case BLOCK_0_BREAKABLE:
        sprite.setSprite(4*16, 4*16, 0);
        sprite.setSprite(5*16, 4*16, 1);

        hp = 5;
        maxHP = 5;
        break;
    case BLOCK_1_BREAKABLE:
        sprite.setSprite(4*16, 5*16, 0);
        sprite.setSprite(5*16, 5*16, 1);

        hp = 10;
        maxHP = 10;
        break;
    case BLUE_BRICKS:
        sprite.setSprite(0, 6*16, 0);
        sprite.setSprite(16, 6*16, 1);
        sprite.setSprite(2*16, 6*16, 2);
        sprite.setSprite(3*16, 6*16, 3);
        break;
    case GREEN_BRICKS:
        sprite.setSprite(4*16, 6*16, 0);
        sprite.setSprite(5*16, 6*16, 1);
        sprite.setSprite(6*16, 6*16, 2);
        sprite.setSprite(7*16, 6*16, 3);
        break;
    }
}

void Entity::setHP(unsigned int hp)
{
    this->hp = hp;
}

unsigned int Entity::getHP()
{
    return hp;
}

void Entity::setMaxHP(unsigned int maxHP)
{
    this->maxHP = maxHP;
}

unsigned int Entity::getMaxHP()
{
    return maxHP;
}

void Entity::updateCurrent(sf::Time dt)
{
    sprite.update(dt);
}

void Entity::handleEventCurrent(const sf::Event& event)
{
    if(type == Type::PLAYER)
    {
        // handle keyboard input for player movement here TODO
    }
}

void Entity::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

