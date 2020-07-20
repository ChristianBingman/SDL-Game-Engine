/*****************************
 * Title: TextureManager.h
 * Author: Christian Bingman
 * Description: Gives some basic helper functions for managing textures
 * TODO: Move this to a util.h class
*****************************/

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