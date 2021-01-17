#pragma once
//
// Created by m.yasser on 11/26/2020.
//
//class our::Application;
#ifndef CameraController_H
#define CameraController_H
//class our::Application;
#include <application.hpp>
//#include "Components/camera_controller.h"
#include <json/json.hpp>

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
//#include <application.hpp>
//#include <application.hpp>
//class our::Application;

#include "./World.h"
#include <mesh/mesh.hpp>
#include <ECS/Components/MeshRenderer.h>
//#include "input/keyboard.hpp"
//#include "input/mouse.hpp"
#include "Components/Light.h"

//class CameraController;
//using namespace our;

class GameState{

private:
    // CameraController* PointerToCamController;
    std::vector<Light> lights;
    World* WorldPointer;
    std::unordered_map<std::string,our::Mesh*> meshes;
    std::unordered_map<std::string, our::ShaderProgram*> programs;
    std::unordered_map<std::string, Texture*> textures;
    Sound* backGround;




public:
    virtual void onEnter(our::Application* app);
    virtual void onExit(our::Application* app);
    virtual void onImmediateGui(ImGuiIO& io);
    virtual void loadResources(const nlohmann::json& json);
    virtual void attachPrograms(const nlohmann::json& json);
    virtual void onDraw(our::Application* app,double deltaTime);
    virtual void loadNode(const nlohmann::json& json,World* worldPointer,Entity* parent,our::Application* app,Sampler* s);

    // void resume();
    //void update();


};

#endif