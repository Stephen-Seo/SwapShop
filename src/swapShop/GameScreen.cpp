
#include <swapShop/GameScreen.hpp>

GameScreen::GameScreen(StateStack& stack) :
State(stack)
{
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw(Context context)
{
}

bool GameScreen::update(sf::Time dt, Context context)
{
}

bool GameScreen::handleEvent(const sf::Event& event, Context context)
{
}

