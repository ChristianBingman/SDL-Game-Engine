/*
 * Title: Map.h
 * Author: Christian Bingman
 * Description: Allows for loading, managing, and drawing a map based on tiles
 * Date Created: July 26, 2020
 */

// TODO: This won't likely be used in Tetris, but should eventually become more feature full.
// The array doesn't NEED to be dynamic, but needs to fit better into 16 x 9

#pragma once
#include "SDL2/SDL.h"

/*
 * Title: Map
 * + Creates and modifies a map
 */
class Map
{
private:
    SDL_Rect src, dest;

    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;

    // TODO: Make dynamic
    int map[20][25];

public:
    Map();
    ~Map();

    void LoadMap(int arr[20][25]);
    void DrawMap();
};

