/*
 * Title: PhysicsComponent.h
 * Author: Christian Bingman
 * Description: Manages the physics of entities (box collider)
 * Date Created: July 26, 2020
 */

#pragma once

#include "../ECS.h"
#include <SDL2/SDL.h>
#include <vector>
#include "PositionComponent.h"
#include <string>
#include "../Game.h"
#include "../TextureManager.h"

/*
 * Title: PhysicsComponent
 * + Inherits Component, Manages collision boxes and physics of entities
 */
class PhysicsComponent : public Component
{
private:
    std::vector<SDL_Rect> colliders; // List of colliders on an object
    bool debugMode; // Determines if debug info is drawn
    PositionComponent* transform; // Gets the position, so that the boxes are drawn relative
    std::string tag; // Tag for determining what object the collider is colliding with
public:
    void init() override;
    void addTag(std::string tag) {this->tag = tag;}
    void addCollider(int width, int height, int offsetX, int offsetY);
    void draw() override;
};

/*
 * PhysicsComponent::addCollider
 * + Adds a new box collider to the list of colliders. There can be multiple on one object
 *
 * Arguments:
 * + int width - width of the hitbox
 * + int height - height of the hitbox
 * + int offsetX - the offset relative of the objects location (top left)
 * + int offsetY - the offset relative of the objects location (top left)
 *
 * Return Type: void
 */
void PhysicsComponent::addCollider(int width, int height, int offsetX, int offsetY){
    Game::logger->log("Creating collider on " + tag + " with size (" + to_string(width) + ", " + to_string(height) + ")", 1);
    SDL_Rect collider;
    collider.w = width * TextureManager::textureScale;
    collider.h = height * TextureManager::textureScale;
    collider.x = offsetX * TextureManager::textureScale;
    collider.y = offsetY * TextureManager::textureScale;
    colliders.push_back(collider);
}

/*
 * PhysicsComponent::init
 * + Initializes the collider and gets the position component
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
void PhysicsComponent::init() {
    tag = "";
    Game::logger->log("Initializing PhysicsComponent", 1);
    if(!entity->hasComponent<PositionComponent>()){
        entity->addComponent<PositionComponent>();
    }
    transform = &entity->getComponent<PositionComponent>();
    debugMode = true;
}

/*
 * PhysicsComponent::draw
 * + Draws the colliders on screen if debugMode is active
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
void PhysicsComponent::draw(){
    if(debugMode){
        SDL_SetRenderDrawColor(Game::renderer, 255,255,255,SDL_ALPHA_OPAQUE);
        for(SDL_Rect collider : colliders){
            collider.x += transform->x();
            collider.y += transform->y();

            SDL_RenderDrawRect(Game::renderer, &collider);
        }

        
    }
}