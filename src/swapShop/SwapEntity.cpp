
#include <swapShop/SwapEntity.hpp>

SwapEntity::SwapEntity(const sf::Texture& texture) :
sprite(texture),
hp(1),
maxHP(1)
{
    sprite.setSpriteSize(16, 16);
}

void SwapEntity::setHP(unsigned int hp)
{
    this->hp = hp;
}

unsigned int SwapEntity::getHP()
{
    return hp;
}

bool SwapEntity::damageHP(unsigned int amount)
{
    if(amount >= hp)
    {
        hp = 0;
        return true;
    }
    else
    {
        hp -= amount;
        return false;
    }
}

void SwapEntity::healHP(unsigned int amount)
{
    if(amount + hp > maxHP)
    {
        hp = maxHP;
    }
    else
    {
        hp += amount;
    }
}

void SwapEntity::setMaxHP(unsigned int maxHP)
{
    this->maxHP = maxHP;
}

unsigned int SwapEntity::getMaxHP()
{
    return maxHP;
}

