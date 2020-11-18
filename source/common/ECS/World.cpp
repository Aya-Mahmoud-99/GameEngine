//
// Created by Aya on 11/17/2020.
//

#include "World.h"
Entity* World::createEntity() {
    Entity* e=new Entity();
    Entities.push_back(e);
    return e;
}
vector<Entity *> World::getEntities() {
    return Entities;
}