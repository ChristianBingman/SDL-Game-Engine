/*
 * Title: TextureManager.h
 * Author: Christian Bingman
 * Description: Manages textures and provides utility functions
 * Date Created: July 26, 2020
 */

#pragma once
#include "SDL2/SDL.h"
#include <string>

/*
 * Title: TextureManager
 * + Functions for managing textures
 */
class TextureManager
{
public:
    static SDL_Texture* load(std::string filename);
    static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
    // TODO: Actually scale things dammit, gets converted into integer which most of the time is 1 :(
    static double textureScale;
    static void setTexScale(int desiredWidth, int desiredHeight, int actualWidth, int actualHeight);
};