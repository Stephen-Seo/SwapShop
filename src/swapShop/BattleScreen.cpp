
#include <swapShop/BattleScreen.hpp>

#include <cmath>

#include <engine/resourceIdentifiers.hpp>
#include <engine/resourceManager.hpp>
#include <swapShop/SwapContext.hpp>
#include <swapShop/SwapEntity.hpp>
#include <swapShop/SwapUtility.hpp>
#include <swapShop/entities/YellowGuy.hpp>

BattleScreen::BattleScreen(StateStack& stateStack, Context context) :
State(stateStack, context),
overlay(sf::Vector2f(720.0f, 480.0f)),
phase(START),
enemySpriteTimer(0.0f),
enemySpriteFrames(1),
currentEnemySpriteFrame(0),
enemyHealthBar(140.0f, 10.0f),
playerHealthBar(720.0f, 10.0f),
isPhaseTimeCached(false),
dis(0,5),
sequenceIndex(0),
attackSuccess(0),
attackIndex(0),
attackEnded(false)
{
    if(context.swapContext->player != nullptr && context.swapContext->enemy != nullptr)
    {
        player = dynamic_cast<SwapEntity*>(context.swapContext->player);
        enemy = dynamic_cast<SwapEntity*>(context.swapContext->enemy);
    }

    tset.insert(Textures::SpriteSheet);
    tset.insert(Textures::InputSheet);
    fset.insert(Fonts::ClearSans);
    context.resourceManager->loadResources(getNeededResources());

    overlay.setFillColor(sf::Color(0, 0, 0, 170));

    timer = getPhaseTime(phase, context);

    displayText.setFont(context.resourceManager->getFont(Fonts::ClearSans));
    displayText.setCharacterSize(24);
    displayText.setColor(sf::Color::White);
    displayText.setPosition(360.0f, 420.0f);
    displayText.setString(SwapUtility::getName(*(context.swapContext->enemy)) + " wants to fight!!");

    enemySprite.setTexture(context.resourceManager->getTexture(Textures::SpriteSheet));
    enemySprite.setSpriteSize(16, 16);
    enemySprite.setScale(8.0f, 8.0f);
    // check against entities
    if(typeid(*(context.swapContext->enemy)) == typeid(YellowGuy))
    {
        enemySprite.setSprite(16 * 2, 16 * 2, 0);
        enemySprite.setSprite(16 * 3, 16 * 2, 1);
        enemySpriteFrames = 2;
    }
    enemySprite.displaySprite(0);
    enemySprite.setOrigin(8.0f, 8.0f);
    enemySprite.setPosition(360.0f, 240.0f);

    enemyHealthBar.setOrigin(70.0f, 5.0f);
    enemyHealthBar.setPosition(360.0f, 330.0f);

    playerHealthBar.setPosition(0.0f, 470.0f);

    buttonSprite.setTexture(context.resourceManager->getTexture(Textures::InputSheet));
    indicatorSprite.setTexture(context.resourceManager->getTexture(Textures::InputSheet));

    sequence.push_back(A_W);
    sequence.push_back(B_A);
    sequence.push_back(RB_SPACE);
    sequence.push_back(X_S);
    sequence.push_back(Y_D);
    sequence.push_back(LB_SHIFT);

    sequenceStatus.push_back(1);
    sequenceStatus.push_back(2);
    sequenceStatus.push_back(0);
    sequenceStatus.push_back(1);
    sequenceStatus.push_back(2);
    sequenceStatus.push_back(0);

    timerIndicator.setFillColor(sf::Color(0, 0, 255, 100));
    timerIndicator.setSize(sf::Vector2f(720.0f, 480.0f));

    std::random_device rd;
    gen.seed(rd());
}

void BattleScreen::draw(Context context)
{
    context.window->draw(overlay);
    context.window->draw(timerIndicator);

    context.window->draw(enemySprite);
    context.window->draw(enemyHealthBar);
    context.window->draw(playerHealthBar);
    context.window->draw(displayText);

    displaySequence(context);
}

bool BattleScreen::update(sf::Time dt, Context context)
{
    if(context.swapContext->player == nullptr || context.swapContext->enemy == nullptr)
    {
        context.swapContext->enemy = nullptr;
        requestStackPop();
        return false;
    }

    centerDisplayText();
    battleLogic(dt, context);
    updateDisplay(dt, context);

    return false;
}

bool BattleScreen::handleEvent(const sf::Event& event, Context context)
{
    switch(phase)
    {
    case ATTACK:
    case DEFEND:
    case DEFEND_EXTRA:
    case RECOVER:
        if(sequenceIndex >= sequence.size())
        {
            break;
        }

        if(event.type == sf::Event::KeyPressed &&
           (event.key.code == sf::Keyboard::W ||
            event.key.code == sf::Keyboard::A ||
            event.key.code == sf::Keyboard::S ||
            event.key.code == sf::Keyboard::D ||
            event.key.code == sf::Keyboard::LShift ||
            event.key.code == sf::Keyboard::RShift ||
            event.key.code == sf::Keyboard::Space))
        {
            if(event.key.code == sf::Keyboard::W && sequence[sequenceIndex] == A_W)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if(event.key.code == sf::Keyboard::A && sequence[sequenceIndex] == B_A)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if(event.key.code == sf::Keyboard::S && sequence[sequenceIndex] == X_S)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if(event.key.code == sf::Keyboard::D && sequence[sequenceIndex] == Y_D)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if((event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift) && sequence[sequenceIndex] == LB_SHIFT)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if(event.key.code == sf::Keyboard::Space && sequence[sequenceIndex] == RB_SPACE)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else
            {
                sequenceStatus[sequenceIndex] = 2;
                ++sequenceIndex;
            }
        }
        else if(event.type == sf::Event::JoystickButtonPressed &&
               (event.joystickButton.button == 0 || // A
                event.joystickButton.button == 1 || // B
                event.joystickButton.button == 2 || // X
                event.joystickButton.button == 3 || // Y
                event.joystickButton.button == 4 || // LB
                event.joystickButton.button == 5)) // RB
        {
            if(event.joystickButton.button == 0 && sequence[sequenceIndex] == A_W)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if(event.joystickButton.button == 1 && sequence[sequenceIndex] == B_A)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if(event.joystickButton.button == 2 && sequence[sequenceIndex] == X_S)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if(event.joystickButton.button == 3 && sequence[sequenceIndex] == Y_D)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if(event.joystickButton.button == 4 && sequence[sequenceIndex] == LB_SHIFT)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else if(event.joystickButton.button == 5 && sequence[sequenceIndex] == RB_SPACE)
            {
                sequenceStatus[sequenceIndex] = 1;
                ++sequenceIndex;
            }
            else
            {
                sequenceStatus[sequenceIndex] = 2;
                ++sequenceIndex;
            }
        }

        if(phase == ATTACK && !attackEnded && sequenceIndex >= sequence.size())
        {
            if(isSequenceSuccess())
            {
                ++attackSuccess;
            }
            if(context.swapContext->playerLevel - 1 > attackIndex)
            {
                randomizeSequence(ATTACK);
                ++attackIndex;
            }
            else
            {
                attackEnded = true;
            }
        }
        break;
    default:
        break;
    }

    return false;
}

float BattleScreen::getPhaseTime(Phase phase, Context context)
{
    switch(phase)
    {
    case START:
        return BATTLE_START_TIME;
    case PRE_ATTACK:
        return BATTLE_PRE_ATTACK_TIME;
    case ATTACK:
        if(!isPhaseTimeCached)
        {
            isPhaseTimeCached = true;
            cachedAttackTime = std::log(1.5f + (float) context.swapContext->playerLevel) * 2.5f;
        }
        return cachedAttackTime;
    case PRE_DEFEND:
        return BATTLE_PRE_DEFEND_TIME;
    case DEFEND:
        return BATTLE_DEFEND_TIME;
    case DEFEND_EXTRA:
        return BATTLE_DEFEND_EXTRA_TIME;
    case PRE_RECOVER:
        return BATTLE_PRE_RECOVER_TIME;
    case RECOVER:
        return BATTLE_RECOVER_TIME;
    case END:
        return BATTLE_END_TIME;
    default:
        return 3.0f;
    }
}

void BattleScreen::centerDisplayText()
{
    sf::FloatRect rect = displayText.getLocalBounds();
    displayText.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
}

void BattleScreen::battleLogic(sf::Time dt, Context context)
{
    timer -= dt.asSeconds();
    if(timer <= 0.0f)
    {
        switch(phase)
        {
        case START:
            // goes to PreAttack
            phase = PRE_ATTACK;
            timerIndicator.setFillColor(sf::Color(255, 255, 0, 100));
            displayText.setString("To attack, press the button sequence in order!!");
            break;
        case PRE_ATTACK:
            // goes to Attack
            phase = ATTACK;
            timerIndicator.setFillColor(sf::Color(255, 120, 0, 100));
            displayText.setString("Press the button sequence in order!!");
            randomizeSequence(ATTACK);
            attackSuccess = 0;
            attackIndex = 0;
            attackEnded = false;
            break;
        case ATTACK:
            // goes to PreDefend
            enemy->damageHP(attackSuccess);
            phase = PRE_DEFEND;
            timerIndicator.setFillColor(sf::Color(255, 255, 0, 100));
            displayText.setString("To defend, press the button sequence in order!!");
            sequence.clear();
            break;
        case PRE_DEFEND:
            // goes to defend
            phase = DEFEND;
            timerIndicator.setFillColor(sf::Color(255, 120, 0, 100));
            displayText.setString("Press the button sequence in order!!");
            randomizeSequence(DEFEND);
            break;
        case DEFEND:
            if(isSequenceSuccess())
            {
                // goes to DefendExtra
                phase = DEFEND_EXTRA;
                timerIndicator.setFillColor(sf::Color(150, 0, 255, 100));
                displayText.setString("BONUS! Press the button sequence, hurry!!");
                randomizeSequence(DEFEND_EXTRA);
            }
            else
            {
                // goes to PreRecover
                phase = PRE_RECOVER;
                timerIndicator.setFillColor(sf::Color(100, 255, 0, 100));
                displayText.setString("To recover, press the button sequence in order!!");
                sequence.clear();
            }
            break;
        case DEFEND_EXTRA:
            if(isSequenceSuccess())
            {
                // goes to PreAttack
                phase = PRE_ATTACK;
                timerIndicator.setFillColor(sf::Color(255, 255, 0, 100));
                displayText.setString("To attack, press the button sequence in order!!");
                sequence.clear();
            }
            else
            {
                // goes to PreRecover
                phase = PRE_RECOVER;
                timerIndicator.setFillColor(sf::Color(100, 255, 0, 100));
                displayText.setString("To recover, press the button sequence in order!!");
                sequence.clear();
            }
            break;
        case PRE_RECOVER:
            // goes to Recover
            phase = RECOVER;
            timerIndicator.setFillColor(sf::Color(40, 255, 0, 100));
            displayText.setString("Press the button sequence in order!!");
            randomizeSequence(RECOVER);
            break;
        case RECOVER:
            // goes to PreAttack
            phase = PRE_ATTACK;
            timerIndicator.setFillColor(sf::Color(255, 255, 0, 100));
            displayText.setString("To attack, press the button sequence in order!!");
            sequence.clear();
            break;
        case END:
            break;
        }
        timer = getPhaseTime(phase, context);
    }
}

void BattleScreen::updateDisplay(sf::Time dt, Context context)
{
    enemySpriteTimer += dt.asSeconds();
    if(enemySpriteTimer >= ENEMY_SPRITE_ANIMATION_TIME)
    {
        enemySpriteTimer = 0.0f;
        currentEnemySpriteFrame = (currentEnemySpriteFrame + 1) % enemySpriteFrames;
        enemySprite.displaySprite(currentEnemySpriteFrame);
    }
    enemySprite.update(dt);
    enemyHealthBar.setHP((float) enemy->getHP() / (float) enemy->getMaxHP());
    enemyHealthBar.update(dt);

    playerHealthBar.setHP((float) player->getHP() / (float) player->getMaxHP());
    playerHealthBar.update(dt);

    float percentage = timer / getPhaseTime(phase, context);
    timerIndicator.setSize(sf::Vector2f(720.0f, 480.0f * percentage));
    timerIndicator.setPosition(0.0f, 240.0f * (1.0f - percentage));
}

void BattleScreen::displaySequence(Context context)
{
    if(sequence.empty())
    {
        return;
    }

    float startPosition = 360.0f - (getSequenceWidth() / 2.0f) + 48.0f;
    buttonSprite.setPosition(startPosition, BATTLE_SEQUENCE_DISPLAY_Y);
    for(auto siter = sequence.begin(); siter != sequence.end(); ++siter)
    {
        switch(*siter)
        {
        case A_W:
            buttonSprite.setTextureRect(sf::IntRect(0, 0, 32, 64));
            buttonSprite.setOrigin(16.0f, 32.0f);
            context.window->draw(buttonSprite);
            buttonSprite.move(96.0f, 0.0f);
            break;
        case B_A:
            buttonSprite.setTextureRect(sf::IntRect(32, 0, 32, 64));
            buttonSprite.setOrigin(16.0f, 32.0f);
            context.window->draw(buttonSprite);
            buttonSprite.move(96.0f, 0.0f);
            break;
        case X_S:
            buttonSprite.setTextureRect(sf::IntRect(64, 0, 32, 64));
            buttonSprite.setOrigin(16.0f, 32.0f);
            context.window->draw(buttonSprite);
            buttonSprite.move(96.0f, 0.0f);
            break;
        case Y_D:
            buttonSprite.setTextureRect(sf::IntRect(96, 0, 32, 64));
            buttonSprite.setOrigin(16.0f, 32.0f);
            context.window->draw(buttonSprite);
            buttonSprite.move(96.0f, 0.0f);
            break;
        case LB_SHIFT:
            buttonSprite.setTextureRect(sf::IntRect(128, 0, 64, 64));
            buttonSprite.setOrigin(32.0f, 32.0f);
            context.window->draw(buttonSprite);
            buttonSprite.move(96.0f, 0.0f);
            break;
        case RB_SPACE:
            buttonSprite.setTextureRect(sf::IntRect(192, 0, 64, 32));
            buttonSprite.setOrigin(32.0f, 16.0f);
            buttonSprite.move(0.0f, -16.0f);
            context.window->draw(buttonSprite);
            buttonSprite.move(0.0f, 32.0f);
            buttonSprite.setTextureRect(sf::IntRect(192, 32, 96, 32));
            buttonSprite.setOrigin(48.0f, 16.0f);
            context.window->draw(buttonSprite);
            buttonSprite.move(96.0f, -16.0f);
            break;
        }
    }

    indicatorSprite.setPosition(startPosition, BATTLE_SEQUENCE_DISPLAY_Y);
    for(auto siter = sequenceStatus.begin(); siter != sequenceStatus.end(); ++siter)
    {
        switch(*siter)
        {
        case 0:
            indicatorSprite.move(96.0f, 0.0f);
            break;
        case 1:
            indicatorSprite.setTextureRect(sf::IntRect(288, 0, 64, 64));
            indicatorSprite.setOrigin(32.0f, 32.0f);
            context.window->draw(indicatorSprite);
            indicatorSprite.move(96.0f, 0.0f);
            break;
        case 2:
            indicatorSprite.setTextureRect(sf::IntRect(352, 0, 64, 64));
            indicatorSprite.setOrigin(32.0f, 32.0f);
            context.window->draw(indicatorSprite);
            indicatorSprite.move(96.0f, 0.0f);
            break;
        }
    }
}

float BattleScreen::getSequenceWidth()
{
    float width = 0.0f;
    for(int i = 0; i < sequence.size(); ++i)
    {
        width += 96.0f;
    }
    return width;
}

void BattleScreen::randomizeSequence(Phase phase)
{
    sequence.clear();
    sequenceStatus.clear();

    sequenceIndex = 0;

    switch(phase)
    {
    case ATTACK:
    {
        int sequences;
        if(dis(gen) > 2)
        {
            sequences = 3;
        }
        else
        {
            sequences = 4;
        }
        for(int i = 0; i < sequences; ++i)
        {
            sequence.push_back(static_cast<Button>(dis(gen)));
            sequenceStatus.push_back(0);
        }
        break;
    }
    case DEFEND:
        for(int i = 0; i < 4; ++i)
        {
            sequence.push_back(static_cast<Button>(dis(gen)));
            sequenceStatus.push_back(0);
        }
        break;
    case DEFEND_EXTRA:
        for(int i = 0; i < 7; ++i)
        {
            sequence.push_back(static_cast<Button>(dis(gen)));
            sequenceStatus.push_back(0);
        }
        break;
    case RECOVER:
        for(int i = 0; i < 6; ++i)
        {
            sequence.push_back(static_cast<Button>(dis(gen)));
            sequenceStatus.push_back(0);
        }
        break;
    default:
        break;
    }
}

bool BattleScreen::isSequenceSuccess()
{
    if(sequenceStatus.empty())
    {
        return false;
    }

    for(auto siter = sequenceStatus.begin(); siter != sequenceStatus.end(); ++siter)
    {
        if(*siter != 1)
        {
            return false;
        }
    }

    return true;
}

int BattleScreen::getSequenceCorrect()
{
    if(sequenceStatus.empty())
    {
        return 0;
    }

    int correct = 0;
    for(auto siter = sequenceStatus.begin(); siter != sequenceStatus.end(); ++siter)
    {
        if(*siter == 1)
        {
            ++correct;
        }
    }

    return correct;
}

