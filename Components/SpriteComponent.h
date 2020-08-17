/*
 * Title: SpriteComponent.h
 * Author: Christian Bingman
 * Description: Manages the sprites of entities
 * Date Created: July 26, 2020
 */

#pragma once

#include "../ECS.h"
#include "SDL.h"
#include "PositionComponent.h"
#include "../TextureManager.h"

/*
 * Title: SpriteComponent
 * + Inherits Component, Class for managing the sprites of entities
 */
class SpriteComponent : public Component
{
private:
    PositionComponent *position;
    SDL_Texture* tex;
    SDL_Rect srcRect, destRect;
public:
    SpriteComponent() = default;

    /*
     * SpriteComponent::SpriteComponent
     * + Loads the sprite onto an entity and scaling
     *
     * Arguments:
     * + const char* filename - the asset path
     * + int srcWidth = 32 - the width of the source asset
     * + int srcHeight = 32 - the height of the source asset
     * + int destWidth = 64 - the desired asset width
     * + int destHeight = 64 - the desired asset height
     *
     * Return Type: void
     */
    SpriteComponent(const char* filename, int srcWidth = 32, int srcHeight = 32, int destWidth = 64, int destHeight = 64){
       tex = TextureManager::load(filename);
       srcRect.w = srcWidth * TextureManager::textureScale;
       srcRect.h = srcHeight * TextureManager::textureScale;
       destRect.w = destWidth * TextureManager::textureScale;
       destRect.h = destHeight * TextureManager::textureScale;
       srcRect.x = srcRect.y = 0;
       destRect.x = destRect.y = 0;
    }

    /*
     * SpriteComponent::init
     * + Gets the position component and sets initial coordinates
     *
     * Arguments:
     * + None
     *
     * Return Type: void
     */
    void init() override{
        // TODO: Add checking for the component
        position = &entity->getComponent<PositionComponent>();
        destRect.x = position->x();
        destRect.y = position->y();
    }

    /*
     * SpriteComponent::update
     * + Grabs the position from the position component and dets the render location
     *
     * Arguments:
     * + None
     *
     * Return Type: void
     */
    void update() override{
        destRect.x = position->x();
        destRect.y = position->y();
    }

    /*
     * SpriteComponent::draw
     * + Calls the helper function to draw the sprite
     *
     * Arguments:
     * + None
     *
     * Return Type: void
     */
    void draw() override{
        TextureManager::Draw(tex, srcRect, destRect);
    }
};