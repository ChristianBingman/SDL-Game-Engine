/*
 * Title: Game.cpp
 * Author: Christian Bingman
 * Description: Game header functions
 * Date Created: July 26, 2020
 */

#include "Game.h"
#include <iostream>
#include "Map.h"
#include "ECS.h"


SDL_Renderer* Game::renderer = nullptr; // Static - Must be accessible from other classes
Logger* Game::logger = nullptr; // Static - Also must be accessible from other classes
int Game::screen_width; // Keep the screen width accessible TODO: Add scaling
int Game::screen_height; // Keep the screen height accessible TODO: Add scaling
bool Game::isRunning; // Determine if the game is running from anywhere
InputManager Game::inputManager; // Global input manager
Manager entityManager; // Global entity manager
const int INTERNAL_RESOLUTION_WIDTH = 1280;
const int INTERNAL_RESOLUTION_HEIGHT = 720;




/*
 * Game::Game
 * + Create the texture manager and assign the global logger and entity manager
 *
 * Arguments:
 * + Logger* logger - assings the static logger for global access
 *
 * Return Type: void
 */
Game::Game(Logger* logger){
    Game::logger = logger;
}

/*
 * Game::~Game
 * + Calls the cleanup method
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
Game::~Game(){
    clean();
}

/*
 * Game::init
 * + Initializes the main gmae loop and assigns integrals variables
 *
 * Arguments:
 * + const char* title - title for the window
 * + int xPos - X Position for the window to be located on creation
 * + int yPos - Y Position for the window to be located on creation
 * + int width - Window width
 * + int height - Window height
 * + bool fullscreen - Whether or not to be fullscreen
 *
 * Return Type: void
 */
void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen){
    int flags = 0;
    Game::screen_width = width;
    Game::screen_height = height;
    Game::logger->log("Height: " + to_string(height) + " Width: " + to_string(width), 1);

    // If fullscreen is enabled, enable the fullscreen flag
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
        Game::logger->log("Game is fullscreen", 1);
    }else{
        flags = SDL_WINDOW_SHOWN;
    }

    // Initialize everything, we may need everything in the future, but maybe we can slim this down?
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        
        logger->log("SDL Initialized", 1);

        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
        if(window){
            logger->log("Window Created", 1);
        }else
        {
            logger->log("SDL_CreateWindow: Could not be created!", 3);
        }
        

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            logger->log("Renderer Created", 1);
        }else
        {
            logger->log("SDL_CreateRenderer: Could not be created!", 3);
        }
        
        isRunning = true;
        TextureManager::setTexScale(width, height, INTERNAL_RESOLUTION_WIDTH, INTERNAL_RESOLUTION_HEIGHT);
        level1.build(entityManager);

    } else {
        isRunning = false;
    }
}


/*
 * Game::update
 * + Calls the entityManger update function, which calls the entity update functions
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
void Game::update(){
    entityManager.update();
}

/*
 * Game::render
 * + Clears the screen and calls the draw function of each entity
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
void Game::render(){
    SDL_RenderClear(renderer);
    entityManager.draw();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(renderer);
}

/*
 * Game::clean
 * + Calls destructors for most of the game objects
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
void Game::clean(){
    // TODO: improve memory cleanup, preferably with Valgrind
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    logger->log("Shutting Down SDL", 2);
}

/*
 * Game::running
 * + Returns the current running state of the game
 *
 * Arguments:
 * + None
 *
 * Return Type: bool
 */
bool Game::running(){
    return Game::isRunning;
}