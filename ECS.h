/*
 * Title: ECS.h
 * Author: Let's Make Games
 * Documentation and Cleanup: Christian Bingman
 * Description: LMG's implementation of an Entity Component system.
 * Source: https://www.youtube.com/watch?v=XsvI8Sng6dk
 * Date Created: July 26, 2020
 */

// TODO: Replace this implementation with a better one

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>


class Component;
class Entity;

// Assert that ComponentID is of type size_t
using ComponentID = std::size_t;

/*
 * getComponentTypeID
 * + Returns a component id that will never be the same for any two components
 * because the id is static. Inline function will be inserted into the place it
 * is called instead of being called as a function
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
inline ComponentID getComponentTypeID(){
    static ComponentID lastID = 0;
    return lastID++;
}

/*
 * getComponentTypeID<template>
 * + Returns the component ID of an existing component otherwise
 * a new ID is generated
 *
 * Arguments:
 * + None
 *
 * Return Type: void
 */
template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

/*
 * An arbitrary value defining the max number of components that can be attached to an object.
 * If we max it out then we'll be banging our heads against the wall until we find this number :)
 */
constexpr std::size_t maxComponents = 32;

// Bit sets allow for quick comparisons of bits to tell whether something exists on an object
using ComponentBitSet = std::bitset<maxComponents>;

/* 
 * std::array is a C++ implementation of C fixed sized arrays with the ability to determine
 * it's own size as well as not becoming <T>* but still being assignable
 * For mote info: https://en.cppreference.com/w/cpp/container/array
 */
using ComponentArray = std::array<Component*, maxComponents>;

/*
 * Title: Component
 * + Class used for inheritance by Entity Components
 */
class Component
{
public:
    Entity* entity;
    
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

/*
 * Title: Entity
 * + Manages how entities are located in memory and calls entity component functions
 */
class Entity
{
private:
    bool active;

    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
public:

    /*
     * Entity::Entity
     * + Entity constructor that says the entity is active
     *
     * Arguments:
     * + None
     *
     * Return Type: void
     */
    Entity(){
        active = true;
    }

    /*
     * Entity::update
     * + Calls the component update functions
     *
     * Arguments:
     * + None
     *
     * Return Type: void
     */
    void update() {
        for(auto& c : components) c->update();
    }

    /*
     * Entity::draw
     * + Calls the draw functions of components
     *
     * Arguments:
     * + None
     *
     * Return Type: void
     */
    void draw() {
        for(auto& c : components) c->draw();
    }

    /*
     * Entity::isActive
     * + Returns the current state of an entity
     *
     * Arguments:
     * + None
     *
     * Return Type: bool
     */
    bool isActive() const { return active; }

    void destroy() { active = false; }

    /*
     * Entity::hasComponent
     * + Determines if an entity has a component by comparing the bitset
     *
     * Arguments:
     * + template <typename T> - The component that is being checked for
     *
     * Return Type: bool
     */
    template <typename T> bool hasComponent() const {
        return componentBitSet[getComponentTypeID<T>()];
    }

    /*
     * Entity::addComponent
     * + Adds a component to an entity by creating the component and adding it 
     * to its arsenal of components. For world domination.
     * I dunno why it needs &&, but I'll figure it out eventually
     *
     * Arguments:
     * + template <typename T> - The name of the component
     * + TArgs... - Arguments that will be passed to the component's constructor
     *
     * Return Type: T& - Reference to component
     */
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs){
        // Forwards the arguments passed into TArgs into the component constructor
        T* component(new T(std::forward<TArgs>(mArgs)...));

        // This as in class, not function... Why was I confused by this :(
        component->entity = this;

        // More snowflake pointers
        std::unique_ptr<Component> uPtr(component);

        // Move moves the data to the vector instead of copying it
        components.emplace_back(std::move(uPtr));

        // Gets its own ID to ensure it is able to be compared in the bitset
        componentArray[getComponentTypeID<T>()] = component;

        // Sets the correct bit to true
        componentBitSet[getComponentTypeID<T>()] = true;

        component->init();
        return *component;
    }

    /*
     * Entity::getComponent
     * + Returns a reference to an existing coponent on an entity
     *
     * Arguments:
     * + template <typename T> - The component
     *
     * Return Type: Component Reference
     */
    template <typename T> T& getComponent() const {
        // Pulls the component from the array by its ID
        auto ptr(componentArray[getComponentTypeID<T>()]);

        // Converts the unique ptr into a normie pointer then dereferences it which then gets referenced
        return *static_cast<T*>(ptr);
    }


};

/*
 * Title: Manager
 * + Allows for calling simple functions to manage all of the entities at the same time
 */
class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
public:

    /*
     * Manager::update
     * + Calls the update functions of all entities
     *
     * Arguments:
     * + None
     *
     * Return Type: void
     */
    void update(){
        for (auto& e : entities) e->update();
    }

    /*
     * Manager::draw
     * + Calls the draw function of all entities
     *
     * Arguments:
     * + None
     *
     * Return Type: void
     */
    void draw(){
        for (auto& e : entities) e->draw();
    }

    /*
     * Manager::refresh
     * + Removes inActive components by using a higher order reduce function
     *
     * Arguments:
     * + None
     *
     * Return Type: void
     */
    void refresh(){
        entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity){
            return !mEntity->isActive();
        }), std::end(entities));
    }

    /*
     * Manager::addEntity
     * + Declares a new entity unique_ptr and adds it to the entity list
     *
     * Arguments:
     * + Passed as an argument to an entity
     *
     * Return Type: Entity Reference
     */
    Entity& addEntity(){
        Entity* e = new Entity();
        std::unique_ptr<Entity> uPtr(e);
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};
