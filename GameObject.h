#pragma once

#include "SDL2/SDL.h"

class GameObject
{
private:
    int xPos;
    int yPos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
public:
    GameObject(const char* texturesheet);
    ~GameObject();

    void Update();
    void Render();
};
