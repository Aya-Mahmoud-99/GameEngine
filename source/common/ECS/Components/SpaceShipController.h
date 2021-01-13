//
// Created by Aya on 1/13/2021.
//
#include"ECS/Component.h"
#include <../common/application.hpp>
#include "Transform.h"
#include <iostream>

class SpaceShipController: public Component{
our::Application* app;
Transform* T;
glm::vec3 x={0, 0, 0},y={0, 1, 0};
public:
    SpaceShipController(our::Application* application,Transform* Tran);
    void update(double delta_time);
    glm::vec3 Right();
    glm::vec3 Left();
    glm::vec3 Up();
    glm::vec3 Down();
    void GenerateBullet(glm::vec3 position);
};


