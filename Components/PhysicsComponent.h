#pragma once

#include "../ECS.h"
#include <SDL2/SDL.h>
#include <vector>
#include "PositionComponent.h"
#include <string>
#include "../Game.h"

class PhysicsComponent : public Component
{
private:
    std::vector<SDL_Rect> colliders;
    bool debugMode;
    PositionComponent* transform;
    std::string tag;
public:
    void init() override;
    void addTag(std::string tag) {this->tag = tag;}
    void addCollider(int width, int height, int offsetX, int offsetY);
    void draw() override;
};

void PhysicsComponent::addCollider(int width, int height, int offsetX, int offsetY){
    Game::logger->log("Creating collider on " + tag + " with size (" + to_string(width) + ", " + to_string(height) + ")", 1);
    SDL_Rect collider;
    collider.w = width;
    collider.h = height;
    collider.x = offsetX;
    collider.y = offsetY;
    colliders.push_back(collider);
}

void PhysicsComponent::init() {
    tag = "";
    Game::logger->log("Initializing PhysicsComponent", 1);
    if(!entity->hasComponent<PositionComponent>()){
        entity->addComponent<PositionComponent>();
    }
    transform = &entity->getComponent<PositionComponent>();
    debugMode = true;
}

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