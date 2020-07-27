/*
 * Title: Level1.h
 * Author: Christian Bingman
 * Description: Declares level 1's entities and their components
 * Date Created: July 26, 2020
 */

#pragma once

#include "../../ECS.h"

/*
 * Title: Level1
 * + Class for declaring level 1's entities
 */
class Level1
{
public:
    Level1() = default;
    void build(Manager& entities);
    ~Level1();
};

