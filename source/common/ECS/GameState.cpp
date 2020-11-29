
// Created by m.yasser on 11/26/2020.

#include "GameState.h"
#include "./ECS/Components/camera_controller.h"
#include "./shader.hpp"
#include <mesh/mesh.hpp>
#include <mesh/mesh-utils.hpp>
#include <mesh/common-vertex-types.hpp>
#include <mesh/common-vertex-attributes.hpp>
#include <ECS/Components/MeshRenderer.h>



void GameState::onEnter(our::Application* app,World* WorldPointer){
    our::Application* App;
    App=app;
//create our world

 // create a cam entity from world
Entity* CamEntity;
CamEntity=WorldPointer->createEntity();
Transform* TransformCamera=new Transform();
Camera* CameraPointer=new Camera();

    int width, height;
    glfwGetFramebufferSize(app->getWindow(), &width, &height);

    CameraPointer->setupPerspective(glm::pi<float>()/2, static_cast<float>(width)/height, 0.1f, 100.0f);

CameraController* CamControllerPointer=new CameraController(app,CameraPointer);

    CamControllerPointer->setFieldOfViewSensitivity(0.05f );

    CamEntity->addComponent(TransformCamera);
    CamEntity->addComponent(CameraPointer);
    CamEntity->addComponent(CamControllerPointer);


/////////////////////////////////
Entity* Object1;
Transform* TransformObject1=new Transform();

    our::ShaderProgram* program;
    our::Mesh* quad;

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
    Transform* TransformObject2=new Transform();

    our::ShaderProgram* program1;
    our::Mesh quad1;
    our::Mesh* PointerToquad1=&quad1;

    program1->create();
    program1->attach("assets/shaders/ex06_multiple_attributes/multiple_attributes.vert", GL_VERTEX_SHADER);
    program1->attach("assets/shaders/ex04_varyings/varying_color.frag", GL_FRAGMENT_SHADER);
    program1->link();

    our::mesh_utils::loadOBJ(quad1, "assets/models/Suzanne/Suzanne.obj");

    MeshRenderer* MeshPointer1=new MeshRenderer(PointerToquad1,program1);

    Object2->addComponent(TransformObject2);
    Object2->addComponent(MeshPointer1);

////////////////////////////////////////////////////////////////




// from the entitiy , get the camera controller component (generic fn)
//PointerToCamController = camera controller component

}

void GameState::onImmediateGui(ImGuiIO& io){



}

void GameState::onDraw(our::Application* app,World* WorldPointer,double deltaTime){
    our::Application* App;
    App=app;


while(!glfwWindowShouldClose(App->getWindow())){
WorldPointer->getCameraEntity()->getComponent<CameraController>()->update(deltaTime);
WorldPointer->Rendering();
}

onExit(App,WorldPointer);

}

void GameState::onExit(our::Application* app,World* WorldPointer) {
    our::Application* App;
    App=app;

}

//    void resume(){}
//    void update(){}

