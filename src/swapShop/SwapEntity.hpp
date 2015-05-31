
#ifndef SWAP_ENTITY_HPP
#define SWAP_ENTITY_HPP

#include <engine/sceneNode.hpp>
#include <swapShop/SwapSprite.hpp>

class SwapEntity : public SceneNode
{
public:
    SwapEntity(const sf::Texture& texture);

    void setHP(unsigned int hp);
    unsigned int getHP();
    bool damageHP(unsigned int amount);
    void healHP(unsigned int amount);
    void setMaxHP(unsigned int maxHP);
    unsigned int getMaxHP();

protected:
    SwapSprite sprite;
    unsigned int hp;
    unsigned int maxHP;

};

#endif

