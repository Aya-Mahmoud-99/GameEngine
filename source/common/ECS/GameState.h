//
// Created by m.yasser on 11/26/2020.
//
#ifndef CameraController_H
#define CameraController_H

#include <glm/vec2.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <./application.hpp>

#include "./World.h"
#include "input/keyboard.hpp"
#include "input/mouse.hpp"

class CameraController;

class GameState{

private:
     CameraController* PointerToCamController;
public:

    void onEnter(our::Application* app,World* WorldPointer);
    void onExit(our::Application* app,World* WorldPointer);
    void onImmediateGui(ImGuiIO& io);

    void onDraw(our::Application* app,World* WorldPointer,double deltaTime);
   // void resume();
    //void update();


};

#endif
