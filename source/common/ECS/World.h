//
// Created by Aya on 11/17/2020.
//

#ifndef GFX_LAB_WORLD_H
#define GFX_LAB_WORLD_H
#include <glm/glm.hpp>
#include "vector"

class Entity;
using namespace std;

class World {
vector<Entity*> Entities;
public:

    Entity* createEntity(Entity* e);
    //void assignComponentToEntity(Entity* e,Component* c);
    vector<Entity*>& getEntities();
    void Rendering();
    glm::mat4 getCameraEntityTransform();
    Entity* getCameraEntity();
    ~World();
};


#endif //GFX_LAB_WORLD_H
