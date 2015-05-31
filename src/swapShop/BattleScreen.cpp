
#include <swapShop/BattleScreen.hpp>

#include <engine/resourceIdentifiers.hpp>
#include <engine/resourceManager.hpp>
#include <swapShop/SwapContext.hpp>

BattleScreen::BattleScreen(StateStack& stateStack, Context context) :
State(stateStack, context),
overlay(sf::Vector2f(720.0f, 480.0f))
{
    tset.insert(Textures::SpriteSheet);
    tset.insert(Textures::InputSheet);
    fset.insert(Fonts::ClearSans);
    context.resourceManager->loadResources(getNeededResources());

    overlay.setFillColor(sf::Color(0, 0, 0, 170));
}

void BattleScreen::draw(Context context)
{
    context.window->draw(overlay);
}

bool BattleScreen::update(sf::Time dt, Context context)
{
    if(context.swapContext->player == nullptr || context.swapContext->enemy == nullptr)
    {
        requestStackPop();
        return false;
    }

    return false;
}

bool BattleScreen::handleEvent(const sf::Event& event, Context context)
{
    return false;
}

