//
// Created by Aya on 11/17/2020.
//

#include "World.h"
#include "Components\MeshRenderer.h"
#include "Components\Transform.h"
#include "Components\Camera.h"
Entity* World::createEntity() {
    Entity* e=new Entity();
    Entities.push_back(e);
    return e;
}
vector<Entity *> World::getEntities() {
    return Entities;
}

void World::Rendering(){
    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities.at(i)->getComponent<MeshRenderer>()!=NULL)
        {
            Camera* c=Entities.at(i)->getComponent<Camera>();
            Transform* t=Entities.at(i)->getComponent<Transform>();
            glm::mat4 matrix1=t->parents_mat()* c->getProjectionMatrix(); //*view

        }
    }
}