/*
 * Title: PositionComponent.h
 * Author: Christian Bingman
 * Description: Manages the position of an entity
 * Date Created: July 26, 2020
 */

#pragma once

#include "../ECS.h"
#include "../TextureManager.h"

/*
 * Title: PositionComponent
 * + Inherits Component, Controls the global position of an entity
 */
class PositionComponent : public Component
{
private:
    int xpos;
    int ypos;
public:
    // TODO: move these into their own .cpp file
    PositionComponent(){
        xpos = ypos = 0;
    }

    /*
     * PositionComponent::PositionComponent
     * + Initializes the x position and y position
     *
     * Arguments:
     * + int x - initial x position
     * + int y - initial y position
     *
     * Return Type: void
     */
    PositionComponent(int x, int y){
        xpos = x * TextureManager::textureScale;
        ypos = y * TextureManager::textureScale;
    }

    int x() { return xpos; }
    int y() { return ypos; }
    void x(int x) { xpos = x * TextureManager::textureScale; }
    void y(int y) { ypos = y * TextureManager::textureScale; }
    void setPos(int x, int y) { xpos = x * TextureManager::textureScale; ypos = y * TextureManager::textureScale; }
};