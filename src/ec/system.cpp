
#include "system.hpp"

System::System(std::unique_ptr<Node> nodeType) :
nodeType(std::move(nodeType))
{}

bool System::checkEntity(Entity& entity)
{
    if(nodeType->checkEntity(entity))
    {
        std::unique_ptr<Node> nPtr = nodeType->getNewNode();
        nPtr->getCReferencesFromEntity(entity);
        nodeMap.insert(std::make_pair(entity.getID(), std::move(nPtr)));
        return true;
    }
    return false;
}

void System::removeEntity(int eID)
{
    nodeMap.erase(eID);
}

void System::update(sf::Time dt, Context context)
{
    for(auto iter = nodeMap.begin(); iter != nodeMap.end(); ++iter)
    {
        iter->second->update(dt, context);
    }
}
