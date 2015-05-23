
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <engine/sceneNode.hpp>
#include <swapShop/SwapSprite.hpp>

class Entity : public SceneNode
{
public:
    Entity(const sf::Texture& texture, Type type);

    enum Type
    {
        PLAYER,
        RED_GUY,
        YELLOW_GUY,
        COIN,
        HEART,
        POTION,
        BLOCK_0,
        BLOCK_1,
        BLOCK_0_BREAKABLE,
        BLOCK_1_BREAKABLE,
        BLUE_BRICKS,
        GREEN_BRICKS
    }

    void setHP(unsigned int hp);
    unsigned int getHP();
    void setMaxHP(unsigned int maxHP);
    unsigned int getMaxHP();

private:
    SwapSprite sprite;
    unsigned int hp;
    unsigned int maxHP;
    Type type;

    virtual void updateCurrent(sf::Time dt);
    virtual void handleEventCurrent(const sf::Event& event);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif

