//
// Created by Aya on 11/17/2020.
//
#include "Entity.h"
#ifndef GFX_LAB_WORLD_H
#define GFX_LAB_WORLD_H


class World {
vector<Entity*> Entities;
public:
    Entity* createEntity();
    //void assignComponentToEntity(Entity* e,Component* c);
    vector<Entity*> getEntities();
};


#endif //GFX_LAB_WORLD_H
