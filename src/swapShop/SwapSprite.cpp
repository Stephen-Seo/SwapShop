
#include <swapShop/SwapSprite.hpp>

SwapSprite::SwapSprite(const sf::Texture& texture) :
sprite(texture),
sizeX(1),
sizeY(1),
dirty(true),
currentID(0),
flippedHorizontal(false),
flippedVertical(false)
{
    flipperHorizontal.scale(-1.0f, 1.0f, 16.0f, 16.0f);
    flipperVertical.scale(1.0f, -1.0f, 16.0f, 16.0f);
}

SwapSprite::~SwapSprite()
{
}

void SwapSprite::setSpriteSize(int x, int y)
{
    sizeX = x;
    sizeY = y;
    dirty = true;
}

void SwapSprite::setSprite(int x, int y, int id)
{
    spriteMap.insert(std::make_pair(id, std::make_pair(x, y)));
}

void SwapSprite::displaySprite(int id)
{
    currentID = id;
    dirty = true;
}

void SwapSprite::flipHorizontal(bool isTrue)
{
    flippedHorizontal = isTrue;
}

void SwapSprite::flipVertical(bool isTrue)
{
    flippedVertical = isTrue;
}

void SwapSprite::update(sf::Time dt)
{
    if(dirty)
    {
        dirty = false;

        std::pair<int, int>& subRect = spriteMap.at(currentID);

        sprite.setTextureRect(sf::IntRect(subRect.first, subRect.second, sizeX, sizeY));
    }
}

void SwapSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(flippedHorizontal)
    {
        states.transform *= flipperHorizontal;
    }
    if(flippedVertical)
    {
        states.transform *= flipperVertical;
    }

    states.transform *= getTransform(); // TODO verify somehow that this ordering is correct

    target.draw(sprite, states);
}
