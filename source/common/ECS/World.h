//
// Created by Aya on 11/17/2020.
//
#include "./Components/Camera.h"
#include "./Components/Transform.h"
#include "Entity.h"
#ifndef GFX_LAB_WORLD_H
#define GFX_LAB_WORLD_H


class World {
vector<Entity*> Entities;
public:

    Entity* createEntity();
    //void assignComponentToEntity(Entity* e,Component* c);
    vector<Entity*> getEntities();
    void Rendering();
    glm::mat4 getCameraEntityTransform();
    Entity* getCameraEntity();
    ~World();
};


#endif //GFX_LAB_WORLD_H
