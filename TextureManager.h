#pragma once
#include "SDL2/SDL.h"
#include <string>

class TextureManager
{
public:
    TextureManager();
    static SDL_Texture* load(std::string filename);
    static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
    ~TextureManager();
};