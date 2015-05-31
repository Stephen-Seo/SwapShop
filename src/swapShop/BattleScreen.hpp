
#ifndef BATTLE_SCREEN_HPP
#define BATTLE_SCREEN_HPP

#include <engine/state.hpp>

#include <SFML/Graphics.hpp>

class BattleScreen : public State
{
public:
    BattleScreen(StateStack& stateStack, Context context);

    void draw(Context context);
    bool update(sf::Time dt, Context context);
    bool handleEvent(const sf::Event& event, Context context);

private:
    sf::RectangleShape overlay;

};

#endif

