
#include <swapShop/entities/YellowGuy.hpp>

#include <swapShop/SwapUtility.hpp>
#include <swapShop/SwapContext.hpp>

YellowGuy::YellowGuy(const sf::Texture& texture) :
SwapEntity(texture),
phaseTimer(0.0f),
rd(),
gen(rd()),
dis(0, 3),
walkTimer(0.0f),
walkPhase(true)
{
    sprite.setSprite(2*16, 2*16, 0);
    sprite.setSprite(3*16, 2*16, 1);
    sprite.setSprite(4*16, 2*16, 2);
    sprite.setSprite(5*16, 2*16, 3);
    sprite.setSprite(6*16, 2*16, 4);
    sprite.setSprite(7*16, 2*16, 5);
    sprite.setSprite(0, 3*16, 6);
    sprite.setSprite(16, 3*16, 7);
    sprite.setSprite(2*16, 3*16, 8);

    hp = 3;
    maxHP = 3;
}

void YellowGuy::updateCurrent(sf::Time dt, Context context)
{
    walkTimer += dt.asSeconds();
    if(walkTimer >= YELLOW_WALK_TIME)
    {
        walkTimer = 0.0f;
        walkPhase = !walkPhase;
    }

    phaseTimer -= dt.asSeconds();
    if(phaseTimer < 0.0f)
    {
        phase = dis(gen);
        switch(phase)
        {
        case 0:
        case 1:
            phaseTimer = 2.0f;
            break;
        case 2:
            phaseTimer = 0.7f;
            if(context.swapContext->player == nullptr)
            {
                break;
            }
            moveDirection = context.swapContext->player->getPosition() - getPosition();
            SwapUtility::normalize(moveDirection);
            break;
        case 3:
            phaseTimer = 1.3f;
            moveDirection.x = dis(gen) + 1;
            if(dis(gen) > 1)
            {
                moveDirection.x = -moveDirection.x;
            }
            moveDirection.y = dis(gen) + 1;
            if(dis(gen) > 1)
            {
                moveDirection.y = -moveDirection.y;
            }
            SwapUtility::normalize(moveDirection);
            break;
        }
    }

    switch(phase)
    {
    case 0:
    case 1:
        moveDirection.x = 0.0f;
        moveDirection.y = 0.0f;
        break;
    case 2:
        move(moveDirection * YELLOW_MOVEMENT_SPEED * dt.asSeconds());
        break;
    case 3:
        move(moveDirection * YELLOW_MOVEMENT_SPEED / 2.0f * dt.asSeconds());
        break;
    }

    if(moveDirection.x == 0.0f && moveDirection.y == 0.0f)
    {
        sprite.displaySprite(0);
        sprite.flipHorizontal(false);
    }
    else
    {
        switch(SwapUtility::getDirection(moveDirection))
        {
        case 0: // up
            sprite.displaySprite(walkPhase ? 7 : 8);
            break;
        case 1: // down
            sprite.displaySprite(walkPhase ? 1 : 2);
            break;
        case 2: // left
            sprite.displaySprite(walkPhase ? 4 : 5);
            sprite.flipHorizontal(true);
            break;
        case 3: // right
            sprite.displaySprite(walkPhase ? 4 : 5);
            sprite.flipHorizontal(false);
            break;
        }
    }

    sprite.update(dt);
}

void YellowGuy::handleEventCurrent(const sf::Event& event, Context context)
{

}

void YellowGuy::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

