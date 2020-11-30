//
// Created by Aya on 11/17/2020.
//

#include "World.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/camera_controller.h"

#include "Entity.h"
//#include "Components\Camera.h"
Entity* World::createEntity() {
    Entity* e=new Entity();
    Entities.push_back(e);
    return e;
}
vector<Entity *> World::getEntities() {
    return Entities;
}
// this function should be called in main game state 
void World::Rendering(){
    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities[i]->getComponent<MeshRenderer>()!=NULL)
        {
            Camera* c=Entities[i]->getComponent<Camera>();
            Transform* t=Entities[i]->getComponent<Transform>();
            CameraController* cc=Entities[i]->getComponent<CameraController>();
            glm::mat4 vp=c->getProjectionMatrix()*cc->getViewMatrix();
            glm::mat4 matrix1=vp*t->parents_mat(); //*view

            MeshRenderer* mesh=Entities[i]->getComponent<MeshRenderer>();
            our::Mesh* m=mesh->getPointerToMesh();
            our::ShaderProgram* p=mesh->getPointerToProgram();
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(*p);

            p->set("transform", matrix1);
            p->set("tint", glm::vec4(1,1,1,1));
            m->draw();

        }
    }
}
//won't be used;
glm::mat4 World::getCameraEntityTransform(){
    glm::mat4 mat=glm::mat4(1.0);
    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities[i]->getComponent<Camera>()!=NULL)
        {
            Transform* t=Entities[i]->getComponent<Transform>();
            return t->to_mat4();

        }
    }
    return mat;
}
 Entity* World::getCameraEntity(){

    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities.at(i)->getComponent<Camera>()!=NULL)
        {
            return Entities.at(i);
        }
    }
    return NULL;
}
World::~World() {

}