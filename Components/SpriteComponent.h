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
    SpriteComponent(const char* filename){
       tex = TextureManager::load(filename);
    }

    void init() override{
        position = &entity->getComponent<PositionComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = srcRect.h = 32;
        destRect.w = destRect.h = 64;
    }

    void update() override{
        destRect.x = position->x();
        destRect.y = position->y();
    }

    void draw() override{
        TextureManager::Draw(tex, srcRect, destRect);
    }
};