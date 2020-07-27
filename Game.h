/*****************************
 * Title: Game.h
 * Author: Christian Bingman
 * Description: Main class for creating and modifying the SDL window. Activates entity manager.
*****************************/
#pragma once

#include "SDL2/SDL.h"
/*
 * Title: Game.h
 * Author: Christian Bingman
 * Description: Manages main game loop
 * Date Created: July 26, 2020
 */

#include "SDL2/SDL_image.h"
#include "TextureManager.h"
#include "Log.h"
#include "InputManager.h"
#include "Levels/Level1/Level1.h"

/*
 * Title: Game
 * + Methods and variables pertaining to the state and actions in game
 */
class Game
{
private:
    SDL_Window* window;
    TextureManager* texManage;
    void _initializeObjects();
    Level1 level1;
public:
    static SDL_Renderer* renderer;
    static Logger* logger;
    static bool isRunning;
    static InputManager inputManager;
    static int screen_width, screen_height;

    Game(Logger* logger);
    ~Game();

    void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool running();
};
