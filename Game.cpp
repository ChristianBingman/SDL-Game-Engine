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





// Create the texture manager and assign the global logger and entity manager
Game::Game(Logger* logger){
    Game::logger = logger;
    texManage = new TextureManager();
}

Game::~Game(){
    clean();
}

// Initializes SDL
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

        level1.build(entityManager);

    } else {
        isRunning = false;
    }
}


// Calls entities update functions
void Game::update(){
    entityManager.update();
}

// Draws the map and registered entities and renders it
void Game::render(){
    SDL_RenderClear(renderer);
    entityManager.draw();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(renderer);
}

// Calls destructors for most of the game objects
void Game::clean(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    texManage->~TextureManager();
    logger->log("Shutting Down SDL", 2);
}

// Boolean containing the value of whether the game is running
bool Game::running(){
    return Game::isRunning;
}