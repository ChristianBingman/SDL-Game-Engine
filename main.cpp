#include<iostream>
#include "SDL2/SDL.h"
#include "Log.h"
#include "Game.h"


using namespace std;


int main(int argc, char *argv[])
{
    Game* game = nullptr;
    Logger* logger = nullptr;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    logger = new Logger();
    logger->logStartApp();

    game = new Game(logger);
    game->init("Simple SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    while(game->running()) {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    game->clean();
    logger->~Logger();

    return 0;
}
