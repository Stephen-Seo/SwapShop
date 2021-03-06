
#include "sceneNode.hpp"

int SceneNode::IDcounter = 0;
std::set<int> SceneNode::usedIDs;

SceneNode::SceneNode()
{
    while(SceneNode::usedIDs.find(IDcounter) != SceneNode::usedIDs.end())
    {
        ++IDcounter;
    }
    id = IDcounter;
    SceneNode::usedIDs.insert(id);

    parent = nullptr;
}

SceneNode::~SceneNode()
{
    SceneNode::usedIDs.erase(id);
}

void SceneNode::attachChild(SceneNode::Ptr child)
{
    child->parent = this;
    children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(children.begin(), children.end(),
        [&] (SceneNode::Ptr& p) -> bool { return p.get() == &node; });

    assert(found != children.end());

    SceneNode::Ptr result = std::move(*found);
    result->parent = nullptr;
    children.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget& target,
                     sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target,
                            sf::RenderStates states) const
{}

void SceneNode::drawChildren(sf::RenderTarget& target,
                             sf::RenderStates states) const
{
    std::for_each(children.begin(), children.end(),
        [&target, &states] (const SceneNode::Ptr& child) { child->draw(target, states); });
}

void SceneNode::update(sf::Time dt, Context context)
{
    updateCurrent(dt, context);
    updateChildren(dt, context);
}

void SceneNode::updateCurrent(sf::Time, Context context)
{}

void SceneNode::updateChildren(sf::Time dt, Context context)
{
    std::for_each(children.begin(), children.end(),
        [&dt, context] (SceneNode::Ptr& child) { child->update(dt, context); });
}

void SceneNode::handleEvent(const sf::Event& event, Context context)
{
    handleEventCurrent(event, context);
    passEvent(event, context);
}

void SceneNode::handleEventCurrent(const sf::Event& event, Context context)
{}

void SceneNode::passEvent(const sf::Event& event, Context context)
{
    std::for_each(children.begin(), children.end(),
        [&event, context] (const SceneNode::Ptr& child) { child->handleEvent(event, context); });
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode* node = this; node != nullptr; node = node->parent)
        transform = node->getTransform() * transform;

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

void SceneNode::forEach(std::function<void(SceneNode&)> function, bool includeThis)
{
    if(includeThis)
    {
        function(*this);
    }

    for(auto node = children.begin(); node != children.end(); ++node)
    {
        (*node)->forEach(function, true);
    }
}

bool SceneNode::operator ==(const SceneNode& other) const
{
    return id == other.id;
}

