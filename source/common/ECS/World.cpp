//
// Created by Aya on 11/17/2020.
//

#include "World.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"

#include "Components/CameraComponent.h"
#include "Components/Material.h"
#include "Components/Light.h"
#include "Entity.h"
//#include "Components\Camera.h"
Entity* World::createEntity(Entity* e) {
    //=new Entity();
    Entities.push_back(e);
    return e;
}
vector<Entity *>& World::getEntities() {
    return Entities;
}
// this function should be called in main game state 
void World::Rendering(){
    int Size=Entities.size();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<Size;i++)
    {
        if(Entities[i]->getComponent<MeshRenderer>()!=NULL)
        {
            Camera* c=getCameraEntity()->getComponent<Camera>();
            Transform* t=Entities[i]->getComponent<Transform>();
            CameraController* cc=getCameraEntity()->getComponent<CameraController>();
            //if(!c)return;
            //if(!cc)return;
            glm::mat4 vp=c->getProjectionMatrix()*cc->getCameraViewMatrix();
            glm::mat4 matrix1=vp*t->parents_mat(); //*view
            MeshRenderer* mesh=Entities[i]->getComponent<MeshRenderer>();
            our::Mesh* m=mesh->getPointerToMesh();
            our::ShaderProgram* p=mesh->getMaterial()->getPointerToProgram();
            Texture* tex=mesh->getMaterial()->getPointerToTexture();
            Sampler* sam=mesh->getMaterial()->getPointerToSampler();
            if(tex)tex->TextureBind();
            if(sam)sam->SamplerBind(p);
            std::any tint=mesh->getMaterial()->getUniform("tint");

            glm::vec4* Tint = std::any_cast<glm::vec4>(&tint);
            //if(!p)return;
            //if(!m) return;
            //if()
           // if(*p) return;
           // std::cout<<matrix1[0][0]<<" "<<matrix1[0][1]<<" "<<matrix1[0][2]<<" "<<matrix1[0][3]<<std::endl;
           // std::cout<<matrix1[0][0]<<" "<<matrix1[0][1]<<" "<<matrix1[0][2]<<" "<<matrix1[0][3]<<std::endl;
           if(Tint)cout <<(*Tint)[0]<<endl;
           glUseProgram(*p);
           p->set("transform", matrix1);
           p->set("tint", *Tint);
           /////call Entities[i]->getComponent<Texture>()->TextureBind() ////treat texture as comp??????
           ////call SamplerBind()
           m->draw();

        }
    }
}
void World::RenderingSystem(){

//    Some code to get the rendering camera entity.
    Entity* temp=getCameraEntity();
    Camera* c=temp->getComponent<Camera>();
    Transform* cameraTransform=temp->getComponent<Transform>();
    CameraController* cc=getCameraEntity()->getComponent<CameraController>();
    glm::mat4 vp=c->getProjectionMatrix()*cc->getCameraViewMatrix();
//            Collect all the lights

//    Let M be an empty container containing mesh renderers and their distance from the camera.
    std::unordered_multimap<std::shared_ptr<MeshRenderer>,long long> MTransparent;
    std::unordered_multimap<std::shared_ptr<MeshRenderer>,long long> MOpaque;

    for(auto & Entitie : Entities) {

        if (Entitie->getComponent<MeshRenderer>() != nullptr ) {
            Transform* t=Entitie->getComponent<Transform>();
            glm::mat4 matrix1=vp*t->parents_mat();
            auto* tempPtr=Entitie->getComponent<MeshRenderer>();
                if(tempPtr->getMaterial()->getPointerToRenderState()->getTransparency())
                    MTransparent.insert(pair<std::shared_ptr<MeshRenderer>,long long>(tempPtr,distance(cameraTransform,Entitie->getComponent<Transform>())));
                else
                    MOpaque.insert(pair<std::shared_ptr<MeshRenderer>,long long>(tempPtr,distance(cameraTransform,Entitie->getComponent<Transform>())));

        }
    }
    vector<pair<std::shared_ptr<MeshRenderer>,long long>> tmp;
    for (auto& i : MTransparent)
        tmp.push_back(i);
    // sort with descending order.
    sort(tmp.begin(), tmp.end(),
         [&](pair<std::shared_ptr<MeshRenderer>,long long>& a, pair<std::shared_ptr<MeshRenderer>,long long>& b) { return a.second < b.second; });

    //    Loop on all M:
//    Setup the Material:
//    Use the shader program
//    Send transform and camera variables to shader uniforms
//    Send material variables to shader uniforms
//    Send lights to shader uniforms
//    Use the render state to set openGL state

    for (auto& i : MOpaque){
        //    Draw the entity using its attached mesh renderer component
        our::Mesh* m=i.first->getPointerToMesh();
        our::ShaderProgram* p=i.first->getMaterial()->getPointerToProgram();
        Texture* tex=i.first->getMaterial()->getPointerToTexture();
        Sampler* sam=i.first->getMaterial()->getPointerToSampler();
        if(tex)tex->TextureBind();
        if(sam)sam->SamplerBind(p);
        std::any tint=i.first->getMaterial()->getUniform("tint");
        glm::vec4* Tint = std::any_cast<glm::vec4>(&tint);
        if(Tint)cout <<(*Tint)[0]<<endl;
        glUseProgram(*p);
        //p->set("transform", matrix1);
        p->set("tint", *Tint);
        m->draw();
    }
    for (auto& i : tmp){
        //    Draw the entity using its attached mesh renderer component
        our::Mesh* m=i.first->getPointerToMesh();
        our::ShaderProgram* p=i.first->getMaterial()->getPointerToProgram();
        Texture* tex=i.first->getMaterial()->getPointerToTexture();
        Sampler* sam=i.first->getMaterial()->getPointerToSampler();
        if(tex)tex->TextureBind();
        if(sam)sam->SamplerBind(p);
        std::any tint=i.first->getMaterial()->getUniform("tint");
        glm::vec4* Tint = std::any_cast<glm::vec4>(&tint);
        if(Tint)cout <<(*Tint)[0]<<endl;
        glUseProgram(*p);
        //p->set("transform", matrix1);
        p->set("tint", *Tint);
        m->draw();
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
            return t->getMatrix();

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

Entity* World::getLightEntity(){

    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities.at(i)->getComponent<LightComponent>()!=NULL)
        {
            return Entities.at(i);
        }
    }
    return NULL;
}
World::~World() {

}