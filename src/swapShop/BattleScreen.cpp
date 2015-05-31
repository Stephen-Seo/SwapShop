
#include <swapShop/BattleScreen.hpp>

#include <cmath>

#include <engine/resourceIdentifiers.hpp>
#include <engine/resourceManager.hpp>
#include <swapShop/SwapContext.hpp>
#include <swapShop/SwapEntity.hpp>
#include <swapShop/SwapUtility.hpp>

BattleScreen::BattleScreen(StateStack& stateStack, Context context) :
State(stateStack, context),
overlay(sf::Vector2f(720.0f, 480.0f)),
phase(START)
{
    if(context.swapContext->player != nullptr && context.swapContext->enemy != nullptr)
    {
        player = dynamic_cast<SwapEntity*>(context.swapContext->player);
        enemy = dynamic_cast<SwapEntity*>(context.swapContext->enemy);
    }

    tset.insert(Textures::SpriteSheet);
    tset.insert(Textures::InputSheet);
    fset.insert(Fonts::ClearSans);
    context.resourceManager->loadResources(getNeededResources());

    overlay.setFillColor(sf::Color(0, 0, 0, 170));

    timer = getPhaseTime(phase, context);

    display.setFont(context.resourceManager->getFont(Fonts::ClearSans));
    display.setCharacterSize(24);
    display.setColor(sf::Color::White);
    display.setPosition(360.0f, 420.0f);
    display.setString(SwapUtility::getName(*(context.swapContext->enemy)) + " wants to fight!!");
}

void BattleScreen::draw(Context context)
{
    context.window->draw(overlay);

    context.window->draw(display);
}

bool BattleScreen::update(sf::Time dt, Context context)
{
    if(context.swapContext->player == nullptr || context.swapContext->enemy == nullptr)
    {
        context.swapContext->enemy = nullptr;
        requestStackPop();
        return false;
    }

    centerDisplay();

    timer -= dt.asSeconds();
    if(timer <= 0.0f)
    {
        switch(phase)
        {
        case START:
            break;
        case PRE_ATTACK:
            break;
        case ATTACK:
            break;
        case PRE_DEFEND:
            break;
        case DEFEND:
            break;
        case DEFEND_EXTRA:
            break;
        case PRE_RECOVER:
            break;
        case RECOVER:
            break;
        case END:
            break;
        }
        timer = getPhaseTime(phase, context);
    }

    return false;
}

bool BattleScreen::handleEvent(const sf::Event& event, Context context)
{
    return false;
}

float BattleScreen::getPhaseTime(Phase phase, Context context)
{
    switch(phase)
    {
    case START:
        return BATTLE_START_TIME;
    case PRE_ATTACK:
        return BATTLE_PRE_ATTACK_TIME;
    case ATTACK:
        return std::log(1.5f + (float) context.swapContext->playerLevel) * 2.5f;
    case PRE_DEFEND:
        return BATTLE_PRE_DEFEND_TIME;
    case DEFEND:
        return BATTLE_DEFEND_TIME;
    case DEFEND_EXTRA:
        return BATTLE_DEFEND_EXTRA_TIME;
    case PRE_RECOVER:
        return BATTLE_PRE_RECOVER_TIME;
    case RECOVER:
        return BATTLE_RECOVER_TIME;
    case END:
        return BATTLE_END_TIME;
    }
}

void BattleScreen::centerDisplay()
{
    sf::FloatRect rect = display.getLocalBounds();
    display.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
}

