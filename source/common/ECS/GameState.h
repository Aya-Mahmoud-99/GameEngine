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




public:

    void onEnter(our::Application* app);
    void onExit(our::Application* app);
    void onImmediateGui(ImGuiIO& io);
    void loadResources(const nlohmann::json& json);
    void attachPrograms(const nlohmann::json& json);
    void onDraw(our::Application* app,double deltaTime);
    void loadNode(const nlohmann::json& json,World* worldPointer,Entity* parent,our::Application* app,Sampler* s);
   // void resume();
    //void update();


};

#endif
