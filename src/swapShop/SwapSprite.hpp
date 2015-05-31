
#ifndef SWAP_SPRITE_HPP
#define SWAP_SPRITE_HPP

#include <SFML/Graphics.hpp>

class SwapSprite : public sf::Drawable, public sf::Transformable
{
public:
    SwapSprite();
    SwapSprite(const sf::Texture& texture);
    ~SwapSprite();

    void setSpriteSize(int x, int y);
    void setSprite(int x, int y, int id);

    void displaySprite(int id);
    void flipHorizontal(bool isTrue);
    void flipVertical(bool isTrue);

    void setTexture(const sf::Texture& texture);

    void update(sf::Time dt);

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Sprite sprite;
    std::map<int, std::pair<int, int> > spriteMap;
    int sizeX;
    int sizeY;
    bool dirty;
    int currentID;
    bool flippedHorizontal;
    bool flippedVertical;
    sf::Transform flipperHorizontal;
    sf::Transform flipperVertical;
    bool isTextureLoaded;

};

#endif

