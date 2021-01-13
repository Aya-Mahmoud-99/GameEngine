
// Created by myass on 1/10/2021.
//

// Created by m.yasser on 11/26/2020.
//#include <./application.hpp>
#include "utils.hpp"
#include <fstream>
#include "MenuState.h"
#include "Components/CameraComponent.h"
#include "./shader.hpp"
#include <mesh/mesh-utils.hpp>
#include <mesh/common-vertex-types.hpp>
#include <mesh/common-vertex-attributes.hpp>
#include"Entity.h"

void MenuState::onEnter(our::Application *app) {

    cout<<"xxxxxxxx ONENTER"<<endl;
    WorldPointer=new World();
    int width, height;
    glfwGetFramebufferSize(app->getWindow(), &width, &height);
    Entity* CamEntity=new Entity();
    WorldPointer->createEntity(CamEntity);
    Transform* TransformCamera=new Transform({0,0,4},{0, 0, 0},{1, 1, 0});
    Camera* CameraPointer=new Camera();
    std::cout<<glm::pi<float>()/2<<std::endl;
    std::cout<<static_cast<float>(width)/height<<std::endl;
    CameraPointer->setupPerspective(glm::pi<float>()/2, static_cast<float>(width)/height, 0.1f, 100.0f);
    CameraController* CamControllerPointer=new CameraController(app,CameraPointer,TransformCamera);
    //CamControllerPointer->setTransform(TransformCamera);
    CamControllerPointer->setFieldOfViewSensitivity(0.05f );
    CamEntity->addComponent(TransformCamera);
    CamEntity->addComponent(CameraPointer);
    CamEntity->addComponent(CamControllerPointer);
    ////////////////////////////////////////////
    Entity* Object2=new Entity();
    WorldPointer->createEntity(Object2);
    Transform* TransformObject2=new Transform({0,0,-2},{0,0,0},{1,1,1});
    our::ShaderProgram* program1=new our::ShaderProgram();
    //our::ShaderProgram* program1=&program11;
    our::Mesh* PointerToquad1=new our::Mesh();
    //our::Mesh* PointerToquad1=&quad1;
    program1->create();
    program1->attach("assets/shaders/ex06_multiple_attributes/multiple_attributes.vert", GL_VERTEX_SHADER);
    program1->attach("assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
    program1->link();
    Material* m2=new Material(program1);
    our::mesh_utils::loadOBJ(*PointerToquad1, "assets/models/chicken/chicken.obj");
    MeshRenderer* MeshPointer1=new MeshRenderer(PointerToquad1,m2);
    Object2->addComponent(TransformObject2);
    Object2->addComponent(MeshPointer1);

}

void MenuState::onDraw(our::Application *app, double deltaTime) {
    cout<<"xxxxxxxx ONDRAW"<<endl;
    our::Application* App;
    App=app;
/////////////////////////////////////////to be added lightcomp update/////////////////////////////////////////////////
//int light_index = 0;
//const int MAX_LIGHT_COUNT = 16;
//WorldPointer->getLightEntity()->getComponent<LightComponent>()->lightSelect(light_index,MAX_LIGHT_COUNT,program);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//cout<<"xxxxxxxx"<<endl;
    WorldPointer->getCameraEntity()->getComponent<CameraController>()->update(deltaTime);

}

void MenuState::onExit(our::Application *app) {
    //our::Application* App;
    //App=app;
    cout<<"xxxxxxxx ONEXIT"<<endl;


    vector<Entity*> EntitiesToDelete=WorldPointer->getEntities();
    for(int i=0;i<EntitiesToDelete.size();i++){
        vector<Component*> componentsToDelete=EntitiesToDelete[i]->getComponents();
        for(int j=0;j<componentsToDelete.size();j++){
            MeshRenderer* t = nullptr;
            if ((t = dynamic_cast<MeshRenderer*>(componentsToDelete[j])) != nullptr){

                our::ShaderProgram* p=t->getMaterial()->getPointerToProgram();
                p->destroy();
                our::Mesh* m=t->getPointerToMesh();
                m->destroy();
            };
            delete componentsToDelete[j];
        }
        delete EntitiesToDelete[i];
    }
    delete WorldPointer;

}

void MenuState::onImmediateGui(ImGuiIO &io) {}
void MenuState::attachPrograms(const nlohmann::json &json) {}
void MenuState::loadNode(const nlohmann::json &json, World *worldPointer, Entity *parent, our::Application *app,
                         Sampler *s) {}
                         void MenuState::loadResources(const nlohmann::json &json) {}