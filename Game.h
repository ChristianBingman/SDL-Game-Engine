/*****************************
 * Title: Game.h
 * Author: Christian Bingman
 * Description: Main class for creating and modifying the SDL window. Activates entity manager.
*****************************/
#pragma once

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "Log.h"
#include "ECS.h"

class Game
{
private:
    bool isRunning;
    SDL_Window* window;
    TextureManager* texManage;
    void _initializeObjects();

public:
    static SDL_Renderer* renderer;
    

    Game(Logger* logger);
    ~Game();

    void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    static Logger* logger;
    bool running();
};
