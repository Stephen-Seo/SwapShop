
#ifndef BATTLE_SCREEN_HPP
#define BATTLE_SCREEN_HPP

#define BATTLE_START_TIME 3.0f
#define BATTLE_PRE_ATTACK_TIME 3.0f
#define BATTLE_PRE_DEFEND_TIME 3.0f
#define BATTLE_DEFEND_TIME 1.2f
#define BATTLE_DEFEND_EXTRA_TIME 1.5f
#define BATTLE_PRE_RECOVER_TIME 3.0f
#define BATTLE_RECOVER_TIME 1.5f
#define BATTLE_END_TIME 4.0f

#include <engine/state.hpp>

#include <SFML/Graphics.hpp>

class SwapEntity;

class BattleScreen : public State
{
public:
    BattleScreen(StateStack& stateStack, Context context);

    enum Phase
    {
        START,
        PRE_ATTACK,
        ATTACK,
        PRE_DEFEND,
        DEFEND,
        DEFEND_EXTRA,
        PRE_RECOVER,
        RECOVER,
        END
    };

    void draw(Context context);
    bool update(sf::Time dt, Context context);
    bool handleEvent(const sf::Event& event, Context context);

private:
    SwapEntity* player;
    SwapEntity* enemy;

    sf::RectangleShape overlay;
    Phase phase;

    float timer;

    sf::Text display;

    float getPhaseTime(Phase phase, Context context);
    void centerDisplay();

};

#endif

