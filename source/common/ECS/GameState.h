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

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
//#include <application.hpp>
//#include <application.hpp>
//class our::Application;

#include "./World.h"
//#include "input/keyboard.hpp"
//#include "input/mouse.hpp"

//class CameraController;
//using namespace our;
class GameState{

private:
    // CameraController* PointerToCamController;
     World* WorldPointer;
public:

    void onEnter(our::Application* app);
    void onExit(our::Application* app);
    void onImmediateGui(ImGuiIO& io);

    void onDraw(our::Application* app,double deltaTime);
   // void resume();
    //void update();


};

#endif
