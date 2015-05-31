
#ifndef BATTLE_SCREEN_HPP
#define BATTLE_SCREEN_HPP

#define BATTLE_START_TIME 3.0f
#define BATTLE_PRE_ATTACK_TIME 3.0f
#define BATTLE_PRE_DEFEND_TIME 3.0f
#define BATTLE_DEFEND_TIME 2.0f
#define BATTLE_DEFEND_EXTRA_TIME 3.8f
#define BATTLE_PRE_RECOVER_TIME 3.0f
#define BATTLE_RECOVER_TIME 2.7f
#define BATTLE_END_TIME 4.0f

#define ENEMY_SPRITE_ANIMATION_TIME 0.4f

#define BATTLE_SEQUENCE_DISPLAY_Y 80.0f

#include <engine/state.hpp>

#include <random>

#include <SFML/Graphics.hpp>

#include <swapShop/SwapSprite.hpp>
#include <swapShop/HealthBar.hpp>

class SwapEntity;

class BattleScreen : public State
{
public:
    BattleScreen(StateStack& stateStack, Context context);

    void draw(Context context);
    bool update(sf::Time dt, Context context);
    bool handleEvent(const sf::Event& event, Context context);

private:
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

    enum Button
    {
        A_W,
        B_A,
        X_S,
        Y_D,
        LB_SHIFT,
        RB_SPACE
    };

    SwapEntity* player;
    SwapEntity* enemy;

    sf::RectangleShape overlay;
    Phase phase;

    float timer;

    sf::Text displayText;

    SwapSprite enemySprite;
    float enemySpriteTimer;
    int enemySpriteFrames;
    int currentEnemySpriteFrame;
    HealthBar enemyHealthBar;

    HealthBar playerHealthBar;

    sf::Sprite buttonSprite;
    sf::Sprite indicatorSprite;
    std::vector<Button> sequence;
    // 0 - nothing
    // 1 - success
    // 2 - failure
    std::vector<unsigned char> sequenceStatus;

    sf::RectangleShape timerIndicator;

    bool isPhaseTimeCached;
    float cachedAttackTime;

    std::mt19937 gen;
    std::uniform_int_distribution<> dis;

    int sequenceIndex;

    int attackSuccess;
    int attackIndex;

    float getPhaseTime(Phase phase, Context context);
    void centerDisplayText();
    void battleLogic(sf::Time dt, Context context);
    void updateDisplay(sf::Time dt, Context context);
    void displaySequence(Context context);
    float getSequenceWidth();
    void randomizeSequence(Phase phase);
    bool isSequenceSuccess();
    int getSequenceCorrect();

};

#endif

