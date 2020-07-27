/*
 * Title: InputManager.cpp
 * Author: Christian Bingman
 * Description: InputManager Header Functions
 * Date Created: July 26, 2020
 */

#include "InputManager.h"
#include "Game.h"

/*
 * InputManager::InputManager
 * + InputManager Constructor
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
InputManager::InputManager(){
    
}

/*
 * InputManager::update
 * + Checks keys pressed and contains global actions
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
void InputManager::update(){
    SDL_PollEvent(&events);

    // Add global keys here as well as joystick mappings

    if(InputManager::events.type == SDL_QUIT){
        Game::isRunning = false;
    }
}

