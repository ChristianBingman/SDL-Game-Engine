#pragma once

#include "../ECS.h"
#include "SDL2/SDL.h"
#include "PositionComponent.h"
#include "../TextureManager.h"

class SpriteComponent : public Component
{
private:
    PositionComponent *position;
    SDL_Texture* tex;
    SDL_Rect srcRect, destRect;
public:
    SpriteComponent() = default;
    SpriteComponent(const char* filename, int srcWidth = 32, int srcHeight = 32, int destWidth = 64, int destHeight = 64){
       tex = TextureManager::load(filename);
       srcRect.w = srcWidth;
       srcRect.h = srcHeight;
       destRect.w = destWidth;
       destRect.h = destHeight;
       srcRect.x = srcRect.y = 0;
       destRect.x = destRect.y = 0;
    }

    void init() override{
        position = &entity->getComponent<PositionComponent>();
        destRect.x = position->x();
        destRect.y = position->y();
    }

    void update() override{
        destRect.x = position->x();
        destRect.y = position->y();
    }

    void draw() override{
        TextureManager::Draw(tex, srcRect, destRect);
    }
};