
#include <swapShop/GameScreen.hpp>

#include <engine/resourceIdentifiers.hpp>
#include <engine/context.hpp>
#include <engine/resourceManager.hpp>

#include <swapShop/entities/Player.hpp>

GameScreen::GameScreen(StateStack& stack, Context context) :
State(stack, context)
{
    tset.insert(Textures::SpriteSheet);

    context.resourceManager->loadResources(getNeededResources());

    living.attachChild(SceneNode::Ptr(new Player(context.resourceManager->getTexture(Textures::SpriteSheet))));
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw(Context context)
{
    context.window->draw(living);
    context.window->draw(pickups);
    context.window->draw(world);
}

bool GameScreen::update(sf::Time dt, Context context)
{
    living.update(dt, context);
    pickups.update(dt, context);
    world.update(dt, context);
}

bool GameScreen::handleEvent(const sf::Event& event, Context context)
{
    living.handleEvent(event, context);
    pickups.handleEvent(event, context);
    world.handleEvent(event, context);
}

