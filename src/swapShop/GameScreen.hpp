
#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <engine/state.hpp>
#include <engine/sceneNode.hpp>

#include <swapShop/SwapEntity.hpp>

class GameScreen : public State
{
public:
    GameScreen(StateStack& stack, Context context);
    ~GameScreen();

    virtual void draw(Context context);
    virtual bool update(sf::Time dt, Context context);
    virtual bool handleEvent(const sf::Event& event, Context context);

private:
    SceneNode living;
    SceneNode pickups;
    SceneNode world;

#ifndef NDEBUG
    sf::Text cinputDisplay;
    sf::Text cinputDisplay2;
    sf::Text cinputDisplay3;

    void displayControllerInput(const sf::Event& event);
#endif

};

#endif

