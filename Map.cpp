/*
 * Title: Map.cpp
 * Author: Christian Bingman
 * Description: Map header functions
 * Date Created: July 26, 2020
 */

#include "Map.h"
#include "TextureManager.h"
#include "Game.h"
#include <string>


int lvl1[20][25] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0},
    {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

/*
 * Map::Map
 * + Loads in assets / tileset
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
Map::Map()
{
    // TODO: Allow loading from files preferably have the assets needed for the map loaded from a single file
    dirt = TextureManager::load("assets/dirt.png");
    grass = TextureManager::load("assets/grass.png");
    water = TextureManager::load("assets/water.png");
    
    // TODO: Remove when this class becomes dynamic
    LoadMap(lvl1);

    // Will be set by the draw function
    src.x = src.y = dest.x = dest.y = 0;

    // Allow dynamic tile sizes
    src.w = src.h = 32;
    dest.w = dest.h = 16;


}

/*
 * Map::~Map
 * + Map destructor
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
Map::~Map()
{
}

/*
 * Map::LoadMap
 * + Loads map into the not dynamic array
 *
 * Arguments:
 * + int arr[20][25] - A 20 x 25 matrix of integers referencing their respective texture
 *
 * Return Type: void
 */
void Map::LoadMap(int arr[20][25]){
    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            map[row][column] = arr[row][column];
        }
    }
}

/*
 * Map::DrawMap
 * + Draws the map to the screen with TextureManager::Draw()
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
void Map::DrawMap(){
    int type = 0;

    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            type = map[row][column];

            dest.x = column * 16;
            dest.y = row * 16;

            // TODO: Make this dynamic somehow, most likely create a limited number of textures available to be loaded
            switch (type)
            {
            case 0:
                TextureManager::Draw(water, src, dest);
                break;
            case 1:
                TextureManager::Draw(dirt, src, dest);
                break;
            case 2: 
                TextureManager::Draw(grass, src, dest);
                break;
            default:
                std::string log_out = "Invalid Texture Index ";
                log_out.append(std::to_string(row));
                log_out.append(" ");
                log_out.append(std::to_string(column));
                Game::logger->log(log_out, 3);
                break;
            }
        }
    }
}