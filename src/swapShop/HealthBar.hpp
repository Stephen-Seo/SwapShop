
#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#define DEFAULT_RED_SPEED 0.2f

#include <SFML/Graphics.hpp>

class HealthBar : public sf::Transformable, public sf::Drawable
{
public:
    HealthBar();
    HealthBar(float width, float height);
    HealthBar(const sf::Vector2f& size);

    void setSize(float width, float height);
    void setSize(const sf::Vector2f& size);
    void setHP(float percentage);
    void setRedBarSpeed(float timePerPercentage);

    void update(const sf::Time& dt);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::RectangleShape green;
    sf::RectangleShape red;
    sf::Vector2f size;

    float hpPercentage;
    float redSpeed;
    float timer;
};

#endif

