
#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <engine/state.hpp>

class GameScreen : public State
{
public:
    GameScreen(StateStack& stack);
    ~GameScreen();

    virtual void draw(Context context);
    virtual bool update(sf::Time dt, Context context);
    virtual bool handleEvent(const sf::Event& event, Context context);

private:

};

#endif

