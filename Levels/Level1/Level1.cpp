/*
 * Title: Level1.cpp
 * Author: Christian Bingman
 * Description: Level1 header functions
 * Date Created: July 26, 2020
 */

#include "Level1.h"
#include "../../Components/PhysicsComponent.h"
#include "../../Components/PositionComponent.h"
#include "../../Components/SpriteComponent.h"
#include "../../Game.h"

/*
 * Level1::build
 * + Builds and adds components to entities
 *
 * Arguments:
 * + Manager &entityManager - A reference to the global entity manager
 *
 * Return Type: void
 */
void Level1::build(Manager &entityManager){
    Game::logger->log("Building level 1...", 1);
    auto& playerEntity(entityManager.addEntity());
    playerEntity.addComponent<PositionComponent>();
    playerEntity.addComponent<SpriteComponent>("assets/Coin.png");
    playerEntity.addComponent<PhysicsComponent>();
    playerEntity.getComponent<PhysicsComponent>().addTag("Player Collider");
    playerEntity.getComponent<PhysicsComponent>().addCollider(64, 32, 0, 0);
    playerEntity.getComponent<PhysicsComponent>().addCollider(32, 32, 32, 32);

    auto& bigLogo(entityManager.addEntity());
    bigLogo.addComponent<PositionComponent>();
    bigLogo.getComponent<PositionComponent>().setPos(200,200);
    bigLogo.addComponent<SpriteComponent>("assets/Logo.png", 128, 128, 256, 256);
}


/*
 * Level1::~Level1
 * + Destructor for destroying Level1 entities
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
Level1::~Level1()
{
    // TODO: Destroy entities
    Game::logger->log("Level 1 Destroyed...", 2);
}