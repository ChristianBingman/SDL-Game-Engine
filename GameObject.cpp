#include "GameObject.h"
#include "TextureManager.h"
#include <string>
#include "Game.h"


GameObject::GameObject(const char* texturesheet)
{
    objTexture = TextureManager::load(texturesheet);

    std::string logMessage = "GameObject: ";
    logMessage.append(texturesheet);
    logMessage.append(" loaded");
    Game::logger->log(logMessage, 1);
}

void GameObject::Update(){
    xPos = 200;
    yPos = 150;

    srcRect.h = 200;
    srcRect.w = 200;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xPos;
    destRect.y = yPos;
    destRect.w = srcRect.w / 4;
    destRect.h = srcRect.h / 4;
}

void GameObject::Render(){
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject()
{
    Game::logger->log("GameObject Destroyed", 1);
}
