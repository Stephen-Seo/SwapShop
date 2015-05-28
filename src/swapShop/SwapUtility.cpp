
#include <swapShop/SwapUtility.hpp>

#include <cmath>

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

