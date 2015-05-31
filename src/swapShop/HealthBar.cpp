
#include <swapShop/HealthBar.hpp>

HealthBar::HealthBar() :
hpPercentage(1.0f),
redSpeed(DEFAULT_RED_SPEED),
timer(0.0f)
{
    red.setFillColor(sf::Color::Red);
    green.setFillColor(sf::Color::Green);
}

HealthBar::HealthBar(float width, float height) :
hpPercentage(1.0f),
redSpeed(DEFAULT_RED_SPEED),
timer(0.0f)
{
    size.x = width;
    size.y = height;
    red.setFillColor(sf::Color::Red);
    green.setFillColor(sf::Color::Green);
}

HealthBar::HealthBar(const sf::Vector2f& size) :
hpPercentage(1.0f),
redSpeed(DEFAULT_RED_SPEED),
timer(0.0f)
{
    this->size = size;
    red.setFillColor(sf::Color::Red);
    green.setFillColor(sf::Color::Green);
}

void HealthBar::setSize(float width, float height)
{
    size.x = width;
    size.y = height;
}

void HealthBar::setSize(const sf::Vector2f& size)
{
    this->size = size;
}

void HealthBar::setHP(float percentage)
{
    hpPercentage = percentage;
}

void HealthBar::setRedBarSpeed(float timePerPercentage)
{
    redSpeed = timePerPercentage;
}

void HealthBar::update(const sf::Time& dt)
{
    sf::Vector2f newSize = size;
    newSize.x *= hpPercentage;

    green.setSize(newSize);

    if(newSize.x > red.getSize().x)
    {
        red.setSize(newSize);
    }

    timer += dt.asSeconds();
    if(timer >= redSpeed)
    {
        timer = 0.0f;
        if(newSize.x < red.getSize().x)
        {
            sf::Vector2f redNewSize = red.getSize();
            redNewSize.x -= 1.0f;
            if(redNewSize.x < 0.0f)
            {
                redNewSize.x = 0.0f;
            }
            red.setSize(redNewSize);
        }
    }
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    if(red.getSize().x > 0.0f)
    {
        target.draw(red, states);
    }
    if(green.getSize().x > 0.0f)
    {
        target.draw(green, states);
    }
}

