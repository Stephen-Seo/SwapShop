
#include <swapShop/SwapEntity.hpp>

SwapEntity::SwapEntity(const sf::Texture& texture) :
sprite(texture),
hp(1),
maxHP(1)
{
    sprite.setSpriteSize(16, 16);
    sprite.setScale(2.0f, 2.0f);
}

void SwapEntity::setHP(unsigned int hp)
{
    this->hp = hp;
}

unsigned int SwapEntity::getHP()
{
    return hp;
}

void SwapEntity::setMaxHP(unsigned int maxHP)
{
    this->maxHP = maxHP;
}

unsigned int SwapEntity::getMaxHP()
{
    return maxHP;
}

