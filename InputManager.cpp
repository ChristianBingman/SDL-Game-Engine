#include "InputManager.h"
#include "Game.h"

InputManager::InputManager(){
    
}

void InputManager::update(){
    SDL_PollEvent(&events);

    // Add global keys here as well as joystick mappings

    if(InputManager::events.type == SDL_QUIT){
        Game::isRunning = false;
    }
}

