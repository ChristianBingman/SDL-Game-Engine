#include "TextureManager.h"
#include "SDL2/SDL_image.h"
#include "Game.h"

TextureManager::TextureManager()
{
    Game::logger->log("Texture Manager Initialized", 1);
}

TextureManager::~TextureManager()
{
    Game::logger->log("Texture Manager Destroyed", 2);
}

SDL_Texture* TextureManager::load(std::string filename){
    SDL_Surface* tmpSurface = IMG_Load(filename.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    Game::logger->log("Texture loaded " + filename, 1);

    return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}