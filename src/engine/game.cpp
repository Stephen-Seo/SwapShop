
#include "game.hpp"

#include <swapShop/GameScreen.hpp>

// set packfile name/filepath if one is being used
#define PACKFILE_NAME ""

// set to true if a packfile is being used
#define IS_USING_PACKFILE false

// if not using cmake to build and using the ResourcePacker lib,
// define ResourcePacker_FOUND


#if defined(ResourcePacker_FOUND)
#else
#  define IS_USING_PACKFILE false
#endif

#if IS_USING_PACKFILE == true
#  define RESOURCE_MANAGER_MODE GameResources::PACKFILE
#else
#  define RESOURCE_MANAGER_MODE GameResources::DEFAULT
#endif

Game::Game()
: window(sf::VideoMode(720,480), "SFML App"),
resourceManager(&stateStack, RESOURCE_MANAGER_MODE, PACKFILE_NAME),
mPlayer(),
sPlayer(),
stateStack(),
context(window, resourceManager, mPlayer, sPlayer, ecEngine, isQuitting, clearColor, swapContext),
isQuitting(false),
clearColor()
{
    registerResources();
    registerStates();

    frameTime = sf::seconds(1.f / 60.f);
    window.setFramerateLimit(60); // Added based on PuzzleChaser
}

void Game::run()
{
    sf::Clock clock;
    sf::Time lastUpdateTime = sf::Time::Zero;
    while (window.isOpen() && !isQuitting)
    {
        lastUpdateTime += clock.restart();
        while (lastUpdateTime > frameTime)
        {
            lastUpdateTime -= frameTime;
            processEvents();
            update(frameTime);
        }
        draw();
    }

    if(window.isOpen())
        window.close();
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        stateStack.handleEvent(event, context);
        if(event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(sf::Time deltaTime)
{
    stateStack.update(deltaTime, context);
}

void Game::draw()
{
    window.clear(clearColor);
    stateStack.draw(context);
    window.display();
}

// register resources via resourceManager
// Resource IDs must be listed in resourceIdentifiers.hpp
void Game::registerResources()
{
    resourceManager.registerTexture(Textures::SpriteSheet, "res/spritesheet.png");

    resourceManager.registerFont(Fonts::ClearSans, "res/ClearSans-Regular.ttf");
}

// register states via stateStack
// State IDs must be listed in stateIdentifiers.hpp
void Game::registerStates()
{
    stateStack.registerState<GameScreen>(States::Game, context);

    stateStack.pushState(States::Game);
}
