
// Created by m.yasser on 11/26/2020.
//#include <./application.hpp>
#include "GameState.h"
#include "Components/CameraComponent.h"
#include "./shader.hpp"
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>
#include <mesh/common-vertex-types.hpp>
#include <mesh/common-vertex-attributes.hpp>
#include <ECS/Components/MeshRenderer.h>
#include"Components/Camera.h"
#include"Entity.h"


void GameState::onEnter(our::Application* app){
    our::Application* App;
    //App=app;
//create our world
    WorldPointer=new World();

 // create a cam entity from world
    int width, height;

    glfwGetFramebufferSize(app->getWindow(), &width, &height);
    Entity* CamEntity;
CamEntity=WorldPointer->createEntity();
Transform* TransformCamera=new Transform({0,0,4},{0, 0, 0},{width, height, 0});
Camera* CameraPointer=new Camera();


    CameraPointer->setupPerspective(glm::pi<float>()/2, static_cast<float>(width)/height, 0.1f, 100.0f);

    CameraController* CamControllerPointer=new CameraController(app,CameraPointer,TransformCamera);
    //CamControllerPointer->setTransform(TransformCamera);
    CamControllerPointer->setFieldOfViewSensitivity(0.05f );

    CamEntity->addComponent(TransformCamera);
    CamEntity->addComponent(CameraPointer);
    CamEntity->addComponent(CamControllerPointer);


/////////////////////////////////*/

    Entity* Object1;
    Object1=WorldPointer->createEntity();
    Transform* TransformObject1=new Transform({0,0,0},{0,0,0},{1,1,1});

    our::ShaderProgram* program=new our::ShaderProgram ();
    //our::ShaderProgram* program=&programm;
    //our::Mesh quadd;
    our::Mesh* quad=new our::Mesh();

    program->create();
    program->attach("assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
    program->attach("assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
    program->link();

    // Create a mesh quad with colors passing the elements
    quad->create({our::setup_buffer_accessors<our::ColoredVertex>});
    quad->setVertexData<our::ColoredVertex>(0, {
            {{-0.5, -0.5, 0},{255,   0,   0, 255}},
            {{ 0.5, -0.5, 0},{  0, 255,   0, 255}},
            {{ 0.5,  0.5, 0},{  0,   0, 255, 255}},
            {{-0.5,  0.5, 0},{255, 255,   0, 255}}
    },GL_STATIC_DRAW);
    quad->setElementData<GLuint>({
                                         0, 1, 2,
                                         2, 3, 0
                                 },GL_STATIC_DRAW);

    MeshRenderer* MeshPointer=new MeshRenderer(quad,program);

    Object1->addComponent(TransformObject1);
    Object1->addComponent(MeshPointer);

    ////////////////////////////////////////////////////////
    Entity* Object2;
    Object2=WorldPointer->createEntity();
    Transform* TransformObject2=new Transform({-3,0,0},{0,0,0},{1,1,1});

    our::ShaderProgram* program1=new our::ShaderProgram();
    //our::ShaderProgram* program1=&program11;
    our::Mesh* PointerToquad1=new our::Mesh();
    //our::Mesh* PointerToquad1=&quad1;

    program1->create();
    program1->attach("assets/shaders/ex06_multiple_attributes/multiple_attributes.vert", GL_VERTEX_SHADER);
    program1->attach("assets/shaders/ex04_varyings/varying_color.frag", GL_FRAGMENT_SHADER);
    program1->link();

    our::mesh_utils::loadOBJ(*PointerToquad1, "assets/models/Suzanne/Suzanne.obj");

    MeshRenderer* MeshPointer1=new MeshRenderer(PointerToquad1,program1);

    Object2->addComponent(TransformObject2);
    Object2->addComponent(MeshPointer1);

////////////////////////////////////////////////////////////////


// from the entitiy , get the camera controller component (generic fn)
//PointerToCamController = camera controller component


}

void GameState::onImmediateGui(ImGuiIO& io){



}

void GameState::onDraw(our::Application* app,double deltaTime){
    our::Application* App;
    App=app;

WorldPointer->getCameraEntity()->getComponent<CameraController>()->update(deltaTime);
WorldPointer->Rendering();

}

void GameState::onExit(our::Application* app) {
    our::Application* App;
    App=app;
    delete WorldPointer;


}

//    void resume(){}
//    void update(){}

