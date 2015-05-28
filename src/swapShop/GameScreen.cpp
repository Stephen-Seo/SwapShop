
#include <swapShop/GameScreen.hpp>

#include <engine/resourceIdentifiers.hpp>
#include <engine/context.hpp>
#include <engine/resourceManager.hpp>

#include <swapShop/entities/Player.hpp>
#include <swapShop/entities/BlueBricks.hpp>
#include <swapShop/JoystickIdentifiers.hpp>
#include <swapShop/SwapUtility.hpp>

#include <string>

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
    living.attachChild(SceneNode::Ptr(new Player(context.resourceManager->getTexture(Textures::SpriteSheet))));

    {
        SceneNode::Ptr worldObject(new BlueBricks(context.resourceManager->getTexture(Textures::SpriteSheet)));
        worldObject->setPosition(180.0f, 120.0f);//240.0f);
        world.attachChild(std::move(worldObject));
    }

    indicator.setSize(sf::Vector2f(720.0f, 480.0f));
    indicator.setFillColor(sf::Color::Green);
    colliding = false;

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
    if(colliding)
    {
        context.window->draw(indicator);
    }

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

        if(typeid(current) == typeid(Player))
        {
            this->colliding = !colliding.empty();
        }
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

