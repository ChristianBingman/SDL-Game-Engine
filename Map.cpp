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

Map::Map()
{
    dirt = TextureManager::load("assets/dirt.png");
    grass = TextureManager::load("assets/grass.png");
    water = TextureManager::load("assets/water.png");
    
    LoadMap(lvl1);

    src.x = src.y = dest.x = dest.y = 0;
    src.w = src.h = 32;
    dest.w = dest.h = 16;


}

Map::~Map()
{
}

void Map::LoadMap(int arr[20][25]){
    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            map[row][column] = arr[row][column];
        }
    }
}

void Map::DrawMap(){
    int type = 0;

    for(int row = 0; row < 20; row++){
        for(int column = 0; column < 25; column++){
            type = map[row][column];

            dest.x = column * 16;
            dest.y = row * 16;

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