
#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <memory>
#include <algorithm>
#include <cassert>
#include <functional>
#include <set>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <engine/context.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable,
                  private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;

    SceneNode();
    ~SceneNode();

    void attachChild(Ptr child);
    Ptr detachChild(const SceneNode& node);

    void update(sf::Time dt, Context context);
    void handleEvent(const sf::Event& event, Context context);

    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const;

    void forEach(std::function<void(SceneNode&)> function, bool includeThis = false);

    bool operator ==(const SceneNode& other) const;
private:
    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const;
    void drawChildren(sf::RenderTarget& target,
                      sf::RenderStates states) const;

    virtual void updateCurrent(sf::Time dt, Context context);
    void updateChildren(sf::Time dt, Context context);

    virtual void handleEventCurrent(const sf::Event& event, Context context);
    void passEvent(const sf::Event& event, Context context);

    std::vector<Ptr>    children;
    SceneNode*          parent;
    static int IDcounter;
    static std::set<int> usedIDs;
    int id;

};

#endif
