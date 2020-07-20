#include "Game.h"
#include <iostream>
#include "Map.h"
#include "ECS.h"
#include "Components/PositionComponent.h"
#include "Components/SpriteComponent.h"

SDL_Renderer* Game::renderer = nullptr;
Logger* Game::logger = nullptr;
Manager entityManager;
Map* map;
auto& playerEntity(entityManager.addEntity());

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

    // If fullscreen is enabled, enable the fullscreen flag
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }else{
        flags = SDL_WINDOW_SHOWN;
    }

    // Initialize everything, we may need everything in the future, but maybe we can slim this down?
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        
        logger->log("SDL Initialized", 1);

        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if(window){
            logger->log("Window Created", 1);
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            logger->log("Renderer Created", 1);
        }
        isRunning = true;

        // Initializes our custom objects
        _initializeObjects();
    } else {
        isRunning = false;
    }
}

// Initializes the objects that are added to the game
void Game::_initializeObjects(){
    map = new Map();
    playerEntity.addComponent<PositionComponent>();
    playerEntity.addComponent<SpriteComponent>("assets/Coin.png");
}

/*
 * Determines if the X has been pressed
 * TODO: Add more complex interaction with user
 */
void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
}

// Calls entities update functions
void Game::update(){
    entityManager.update();
}

// Draws the map and registered entities and renders it
void Game::render(){
    SDL_RenderClear(renderer);
    map->DrawMap();
    entityManager.draw();
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
    return isRunning;
}