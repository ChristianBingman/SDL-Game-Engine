#pragma once

#include <SDL2/SDL.h>
#include <vector>

class InputManager
{
private:
    SDL_Event events;
public:
    
    InputManager();
    void update();
};
