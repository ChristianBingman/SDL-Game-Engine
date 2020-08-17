/*
 * Title: TextureManager.cpp
 * Author: Christian Bingman
 * Description: Manages textres and utilities
 * Date Created: July 26, 2020
 */

#include "TextureManager.h"
#include "SDL_image.h"
#include "Game.h"

double TextureManager::textureScale = 1;


/*
 * TextureManager::load
 * + Loads an image and converts it to a texture
 * 
 * Arguments:
 * + string filename - Path to the image file
 * 
 * Return type: SDL_texture*
 */
SDL_Texture* TextureManager::load(std::string filename){
    SDL_Surface* tmpSurface = IMG_Load(filename.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    Game::logger->log("Texture loaded " + filename, 1);

    return texture;
}

/*
 * TextureManager::Draw
 * + Draws a texture to the screen using the Game::renderer
 *
 * Arguments:
 * + SDL_Texture* texture - Pointer to the texture created by TextureManager::load
 * + SDL_Rect src - Actual texture resolution
 * + SDL_Rect dest - Desired texture resolution and location
 *
 * Return Type: void
 */
void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

/*
 * TextureManager::setTexScale
 * + Sets the texture scale
 *
 * Arguments:
 * + int desiredWidth - the desired resolution width
 * + int desiredHeight - the desired resolution height
 * + int actualWidth - the actual resolution width of the game
 * + int actualHeight - the actual resolution height of the game
 *
 * Return Type: void
 */
void TextureManager::setTexScale(int desiredWidth, int desiredHeight, int actualWidth, int actualHeight){
    // TODO: Non integer scaling
    if(floor(desiredWidth / 16) != (desiredWidth / 16) || floor(desiredHeight / 9) != (desiredHeight / 9) || ((desiredWidth / 16) * 9) != desiredHeight){
        Game::logger->log("Desired Resolution is not in 16 x 9 Aspect Ratio", 4);
    }

    TextureManager::textureScale = desiredWidth / actualWidth;

}