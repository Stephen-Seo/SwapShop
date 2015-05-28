
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

