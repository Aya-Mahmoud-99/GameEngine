//
// Created by Aya on 11/17/2020.
//

#include "World.h"
#include "Components\MeshRenderer.h"
#include "Components\Transform.h"
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
        if(Entities.at(i)->getComponent<MeshRenderer>()!=NULL)
        {
            Camera* c=Entities.at(i)->getComponent<Camera>();
            Transform* t=Entities.at(i)->getComponent<Transform>();
            glm::mat4 matrix1=t->parents_mat()* c->getProjectionMatrix(); //*view

            MeshRenderer* mesh=Entities.at(i)->getComponent<MeshRenderer>();
            our::Mesh* m=mesh->getPointerToMesh();
            our::ShaderProgram* p=mesh->getPointerToProgram();
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(p);

            program.set("transform", matrix1);
            program.set("tint", glm::vec4(1,1,1,1));
            mesh.draw();

        }
    }
}
glm::mat4 World::getCameraEntityTransform(){
    glm::mat4 mat=glm::mat4(1.0);
    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities.at(i)->getComponent<Camera>()!=NULL)
        {
            Transform* t=Entities.at(i)->getComponent<Transform>();
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