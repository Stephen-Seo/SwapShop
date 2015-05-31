
#ifndef SWAP_UTILITY_HPP
#define SWAP_UTILITY_HPP

#define ENTITY_SIZE 16
#define ENTITY_SIZE_F float(ENTITY_SIZE)

#include <string>

#include <SFML/System.hpp>

#include <engine/sceneNode.hpp>
#include <engine/context.hpp>

namespace SwapUtility
{
    bool isEntitiesColliding(const SceneNode& one, const SceneNode& two);
    void pushUntilNotColliding(SceneNode& movable, const SceneNode& obstacle);
    void normalize(sf::Vector2f& vector);
    float magnitude(const sf::Vector2f& vector);

    SceneNode::Ptr getRandomBrick(Context context);
    SceneNode::Ptr getRandomBrick(Context context, unsigned int seed);

    // 0 - up
    // 1 - down
    // 2 - left
    // 3 - right
    unsigned char getDirection(const sf::Vector2f& vector);

    std::string getName(const SceneNode& entity);
}

#endif

