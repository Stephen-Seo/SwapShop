
#include <swapShop/SwapUtility.hpp>

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

    // normalize
    SwapUtility::normalize(diff);

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

