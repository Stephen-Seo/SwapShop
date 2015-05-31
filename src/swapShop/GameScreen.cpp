
#include <swapShop/GameScreen.hpp>

#include <engine/resourceIdentifiers.hpp>
#include <engine/context.hpp>
#include <engine/resourceManager.hpp>

#include <swapShop/entities/Player.hpp>
#include <swapShop/entities/BlueBricks.hpp>
#include <swapShop/entities/YellowGuy.hpp>
#include <swapShop/JoystickIdentifiers.hpp>
#include <swapShop/ProceduralGeneration.hpp>
#include <swapShop/SwapUtility.hpp>
#include <swapShop/SwapContext.hpp>

#include <string>
#include <typeinfo>

#ifndef NDEBUG
  #include <iostream>
#endif

GameScreen::GameScreen(StateStack& stack, Context context) :
State(stack, context)
{
    *(context.clearColor) = sf::Color(150,150,150);

    tset.insert(Textures::SpriteSheet);
    fset.insert(Fonts::ClearSans);

    context.resourceManager->loadResources(getNeededResources());

    // init entities
    SceneNode::Ptr player(new Player(context.resourceManager->getTexture(Textures::SpriteSheet)));
    context.swapContext->player = player.get();
    player->setPosition(32.0f, 32.0f);
    living.attachChild(std::move(player));

    generateWorld(context);


#ifndef NDEBUG
    cinputDisplay.setFont(context.resourceManager->getFont(Fonts::ClearSans));
    cinputDisplay.setCharacterSize(20);
    cinputDisplay.setPosition(10.0f, 450.0f);
    cinputDisplay.setColor(sf::Color::White);

    cinputDisplay2.setFont(context.resourceManager->getFont(Fonts::ClearSans));
    cinputDisplay2.setCharacterSize(12);
    cinputDisplay2.setPosition(360.0f, 430.0f);
    cinputDisplay2.setColor(sf::Color::White);

    cinputDisplay3.setFont(context.resourceManager->getFont(Fonts::ClearSans));
    cinputDisplay3.setCharacterSize(12);
    cinputDisplay3.setPosition(360.0f, 450.0f);
    cinputDisplay3.setColor(sf::Color::White);
#endif
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw(Context context)
{
    context.window->draw(living);
    context.window->draw(pickups);
    context.window->draw(world);

#ifndef NDEBUG
    context.window->draw(cinputDisplay);
    context.window->draw(cinputDisplay2);
    context.window->draw(cinputDisplay3);
#endif
}

bool GameScreen::update(sf::Time dt, Context context)
{
    living.update(dt, context);
    pickups.update(dt, context);
    world.update(dt, context);

    checkBattleState(context);

    collideLiving(context);
    collideWorld();

    return false;
}

bool GameScreen::handleEvent(const sf::Event& event, Context context)
{
    living.handleEvent(event, context);
    pickups.handleEvent(event, context);
    world.handleEvent(event, context);

#ifndef NDEBUG
    displayControllerInput(event);
#endif

    return false;
}

void GameScreen::generateWorld(Context context)
{
    std::unordered_set<Coordinate<int> > coords = ProceduralGeneration::drunkardWalk(20, 13, 0.7f, false);

    for(int x = 0; x < 20; ++x)
    {
        for(int y = 0; y < 13; ++y)
        {
            if(coords.find(Coordinate<int>(x, y)) == coords.end())
            {
                // top left
                SceneNode::Ptr worldObject = SwapUtility::getRandomBrick(context);
                worldObject->setPosition(32 + x * 32, 32 + y * 32);
                world.attachChild(std::move(worldObject));

                // top right
                worldObject = SwapUtility::getRandomBrick(context);
                worldObject->setPosition(48 + x * 32, 32 + y * 32);
                world.attachChild(std::move(worldObject));

                // bottom left
                worldObject = SwapUtility::getRandomBrick(context);
                worldObject->setPosition(32 + x * 32, 48 + y * 32);
                world.attachChild(std::move(worldObject));

                // bottom right
                worldObject = SwapUtility::getRandomBrick(context);
                worldObject->setPosition(48 + x * 32, 48 + y * 32);
                world.attachChild(std::move(worldObject));
            }
        }
    }

    // top and bottom edges
    for(int x = 0; x < 45; ++x)
    {
        SceneNode::Ptr worldObject(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(x * 16, 0);
        world.attachChild(std::move(worldObject));

        worldObject = SceneNode::Ptr(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(x * 16, 16);
        world.attachChild(std::move(worldObject));

        worldObject = SceneNode::Ptr(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(x * 16, 464);
        world.attachChild(std::move(worldObject));

        worldObject = SceneNode::Ptr(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(x * 16, 448);
        world.attachChild(std::move(worldObject));
    }

    // left and right edges
    for(int y = 1; y < 29; ++y)
    {
        SceneNode::Ptr worldObject(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(0, y * 16);
        world.attachChild(std::move(worldObject));

        worldObject = SceneNode::Ptr(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(16, y * 16);
        world.attachChild(std::move(worldObject));

        worldObject = SceneNode::Ptr(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(672, y * 16);
        world.attachChild(std::move(worldObject));

        worldObject = SceneNode::Ptr(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(688, y * 16);
        world.attachChild(std::move(worldObject));

        worldObject = SceneNode::Ptr(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(704, y * 16);
        world.attachChild(std::move(worldObject));
    }

    // add enemies
    int enemies = 4;
    while(enemies > 0)
    {
        for(auto coord = coords.begin(); coord != coords.end(); ++coord)
        {
            if(enemies <= 0)
            {
                break;
            }
            if(coord->x > 1 && coord->y > 1)
            {
                SceneNode::Ptr enemy(new YellowGuy(context.resourceManager->getTexture(Textures::SpriteSheet)));
                enemy->setPosition(32 + coord->x * 32, 32 + coord->y * 32);
                living.attachChild(std::move(enemy));
                --enemies;
            }
        }
    }
}

void GameScreen::checkBattleState(Context context)
{
    if(context.swapContext->battleStatus != SwapContext::STANDBY)
    {
        if(context.swapContext->battleStatus == SwapContext::PLAYER_WIN && context.swapContext->enemy != nullptr)
        {
            living.detachChild(*(context.swapContext->enemy));
            context.swapContext->enemy = nullptr;
        }
        else if(context.swapContext->battleStatus == SwapContext::ENEMY_WIN && context.swapContext->player != nullptr)
        {
            living.detachChild(*(context.swapContext->player));
            context.swapContext->player = nullptr;
            context.swapContext->enemy = nullptr;
        }

        context.swapContext->battleStatus = SwapContext::STANDBY;
    }
}

void GameScreen::collideLiving(Context context)
{
    living.forEach([this, context] (SceneNode& current) {
        if(typeid(current) == typeid(Player))
        {
            this->living.forEach([this, &current, context] (SceneNode& other) {
                if(current == other)
                {
                    return;
                }
                else if(SwapUtility::isEntitiesColliding(current, other))
                {
                    context.swapContext->enemy = &other;
                    requestStackPush(States::Battle);
                }
            });
        }
    });
}

void GameScreen::collideWorld()
{
    living.forEach([this] (SceneNode& current) {
        std::vector<SceneNode*> colliding;
        this->world.forEach([&current, &colliding] (SceneNode& worldCurrent) {
            if(SwapUtility::isEntitiesColliding(current, worldCurrent))
            {
                colliding.push_back(&worldCurrent);
            }
        });

        for(auto node = colliding.begin(); node != colliding.end(); ++node)
        {
            SwapUtility::pushUntilNotColliding(current, **node);
        }
    });
}

#ifndef NDEBUG
void GameScreen::displayControllerInput(const sf::Event& event)
{
    if(event.type == sf::Event::JoystickButtonPressed)
    {
        cinputDisplay.setString("Button Pressed: " + std::to_string(event.joystickButton.button));
    }
    else if(event.type == sf::Event::JoystickButtonReleased)
    {
        cinputDisplay.setString("");
    }
    else if(event.type == sf::Event::JoystickMoved)
    {
        if(event.joystickMove.position > JOYSTICK_DEADZONE || event.joystickMove.position < -JOYSTICK_DEADZONE)
        {
            std::string axis;
            std::string axis2;
            switch(event.joystickMove.axis)
            {
                case sf::Joystick::X:
                    axis = "X";
                    break;
                case sf::Joystick::Y:
                    axis2 = "Y";
                    break;
                case sf::Joystick::Z:
                    axis = "Z";
                    break;
                case sf::Joystick::R:
                    axis2 = "R";
                    break;
                case sf::Joystick::U:
                    axis = "U";
                    break;
                case sf::Joystick::V:
                    axis2 = "V";
                    break;
                case sf::Joystick::PovX:
                    axis = "PovX";
                    break;
                case sf::Joystick::PovY:
                    axis2 = "PovY";
                    break;
            }
            if(!axis.empty())
            {
                cinputDisplay2.setString("Axis " + axis + ": " + std::to_string(event.joystickMove.position));
            }
            if(!axis2.empty())
            {
                cinputDisplay3.setString("Axis " + axis2 + ": " + std::to_string(event.joystickMove.position));
            }
        }
    }
}
#endif

