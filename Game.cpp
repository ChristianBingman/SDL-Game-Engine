#include "Game.h"
#include <iostream>
#include "Map.h"
#include "ECS.h"
#include "Components.h"

SDL_Renderer* Game::renderer = nullptr;
Logger* Game::logger = nullptr;
Map* map;
Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game(Logger* logger){
    Game::logger = logger;
    texManage = new TextureManager();
}

Game::~Game(){
    clean();
}

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen){
    int flags = 0;

    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }else{
        flags = SDL_WINDOW_SHOWN;
    }

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

        _initializeObjects();

        isRunning = true;
    } else {
        isRunning = false;
    }
}

void Game::_initializeObjects(){
    player = new GameObject("assets/bird.png");
    map = new Map();
    newPlayer.addComponent<PositionComponent>();
}

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

void Game::update(){
    player->Update();
    manager.update();
    std::cout << newPlayer.getComponent<PositionComponent>().x() << "," << newPlayer.getComponent<PositionComponent>().y() << std::endl;
}

void Game::render(){
    SDL_RenderClear(renderer);
    map->DrawMap();
    // TODO: Add stuff to render
    player->Render();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    texManage->~TextureManager();
    player->~GameObject();
    logger->log("Shutting Down SDL", 2);
}

bool Game::running(){
    return isRunning;
}