
#include "context.hpp"

Context::Context(sf::RenderWindow& window, ResourceManager& resourceManager, MusicPlayer& mPlayer, SoundPlayer& sPlayer, Engine& ecEngine, bool& isQuitting, sf::Color& clearColor, SwapContext& swapContext) :
window(&window),
resourceManager(&resourceManager),
mPlayer(&mPlayer),
sPlayer(&sPlayer),
ecEngine(&ecEngine),
isQuitting(&isQuitting),
clearColor(&clearColor),
swapContext(&swapContext)
{}
