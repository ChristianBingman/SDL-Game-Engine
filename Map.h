/*****************************
 * Title: Map.h
 * Author: Christian Bingman
 * Description: Most of this class should be rewritten to support loading from map files
*****************************/

#pragma once
#include "SDL2/SDL.h"

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

