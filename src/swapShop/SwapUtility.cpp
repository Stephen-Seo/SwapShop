
#include <swapShop/SwapUtility.hpp>

#include <cmath>
#include <random>
#include <typeinfo>

#include <engine/resourceManager.hpp>

#include <swapShop/entities/BlueBricks.hpp>
#include <swapShop/entities/GreenBricks.hpp>

#include <swapShop/entities/Player.hpp>
#include <swapShop/entities/YellowGuy.hpp>

bool SwapUtility::isEntitiesColliding(const SceneNode& one, const SceneNode& two)
{
    sf::Vector2f onePos = one.getWorldPosition();
    sf::Vector2f twoPos = two.getWorldPosition();

    return ((onePos.x >= twoPos.x && onePos.x < twoPos.x + ENTITY_SIZE_F) &&
            (onePos.y >= twoPos.y && onePos.y < twoPos.y + ENTITY_SIZE_F)) ||
           ((onePos.x + ENTITY_SIZE_F >= twoPos.x && onePos.x + ENTITY_SIZE_F < twoPos.x + ENTITY_SIZE_F) &&
            (onePos.y >= twoPos.y && onePos.y < twoPos.y + ENTITY_SIZE_F)) ||
           ((onePos.x >= twoPos.x && onePos.x < twoPos.x + ENTITY_SIZE_F) &&
            (onePos.y + ENTITY_SIZE_F >= twoPos.y && onePos.y + ENTITY_SIZE_F < twoPos.y + ENTITY_SIZE_F)) ||
           ((onePos.x + ENTITY_SIZE_F >= twoPos.x && onePos.x + ENTITY_SIZE_F < twoPos.x + ENTITY_SIZE_F) &&
            (onePos.y + ENTITY_SIZE_F >= twoPos.y && onePos.y + ENTITY_SIZE_F < twoPos.y + ENTITY_SIZE_F));
}

void SwapUtility::pushUntilNotColliding(SceneNode& movable, const SceneNode& obstacle)
{
    // get position vectors
    sf::Vector2f mVec = movable.getWorldPosition();
    sf::Vector2f oVec = obstacle.getWorldPosition();

    // get diff vector
    sf::Vector2f diff = mVec - oVec;

    // get current magnitude of diff
    float magnitude = SwapUtility::magnitude(diff);

    // normalize
    SwapUtility::normalize(diff);

    // move to at least distance of ENTITY_SIZE_F
    if(SwapUtility::isEntitiesColliding(movable, obstacle))
    {
        if(magnitude < ENTITY_SIZE_F)
        {
            diff *= ENTITY_SIZE_F - magnitude;
            movable.move(diff);

            // normalize again
            SwapUtility::normalize(diff);
        }
    }
    else
    {
        return;
    }


    // move until not colliding
    while(SwapUtility::isEntitiesColliding(movable, obstacle))
    {
        movable.move(diff);
    }

    // TODO find a better way to "move" colliding things
}

void SwapUtility::normalize(sf::Vector2f& vector)
{
    vector /= std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float SwapUtility::magnitude(const sf::Vector2f& vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

SceneNode::Ptr SwapUtility::getRandomBrick(Context context)
{
    std::random_device rd;
    return SwapUtility::getRandomBrick(context, rd());
}

SceneNode::Ptr SwapUtility::getRandomBrick(Context context, unsigned int seed)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(0,1);

    switch(dis(gen))
    {
    case 0:
        return SceneNode::Ptr(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
    case 1:
        return SceneNode::Ptr(new GreenBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
    default:
        return SceneNode::Ptr(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
    }
}

// 0 - up
// 1 - down
// 2 - left
// 3 - right
unsigned char SwapUtility::getDirection(const sf::Vector2f& vector)
{
    if(std::abs(vector.x) >= std::abs(vector.y))
    {
        if(vector.x >= 0)
        {
            return 3;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        if(vector.y >= 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

std::string SwapUtility::getName(const SceneNode& entity)
{
    if(typeid(entity) == typeid(Player))
    {
        return "Player";
    }
    else if(typeid(entity) == typeid(YellowGuy))
    {
        return "Yellow Guy";
    }
    return "Unknown";
}

