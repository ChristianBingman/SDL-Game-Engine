/*
 * Title: InputManager.h
 * Author: Christian Bingman
 * Description: Manages Global Inputs
 * Date Created: July 26, 2020
 */

#pragma once

#include <SDL2/SDL.h>
#include <vector>

/*
 * Title: InputManager
 * + Class for managing global inputs
 */
class InputManager
{
private:
    SDL_Event events; // Contains the information about the state of all inputs
public:
    InputManager();
    void update();
};
