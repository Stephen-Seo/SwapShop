
#ifndef SWAP_CONTEXT_HPP
#define SWAP_CONTEXT_HPP

#include <engine/sceneNode.hpp>

class SwapContext
{
public:
    SwapContext();

    enum BattleStatus
    {
        STANDBY,
        PLAYER_WIN,
        ENEMY_WIN
    };

    SceneNode* player;
    SceneNode* enemy;
    BattleStatus battleStatus;
    int playerLevel;

private:

};

#endif

