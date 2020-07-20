/*****************************
 * Title: main.cpp
 * Author: Christian Bingman
 * Description: Custom 2D Game Engine
*****************************/

#include<iostream>
#include "SDL2/SDL.h"
#include "Log.h"
#include "Game.h"


using namespace std;


int main(int argc, char *argv[])
{

    Game* game = nullptr;
    Logger* logger = nullptr;

    // Set the FPS to 60
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    // Initialize Logger and print info
    logger = new Logger();
    logger->logStartApp();

    // Initialize the game class
    game = new Game(logger);

    // TODO: Allow for various output display sizes
    game->init("Simple SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    while(game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        // Determines the amount of 'lag' to put between frames to make it smooth
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    game->clean();
    logger->~Logger();

    return 0;
}
