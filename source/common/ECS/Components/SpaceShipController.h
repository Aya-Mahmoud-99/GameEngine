//
// Created by Aya on 1/13/2021.
//
#pragma once
#include"ECS/Component.h"
#include <../common/application.hpp>
#include "Transform.h"
#include "../Bullet.h"
#include "MeshRenderer.h"
#include <iostream>
#include "../Sound.h"

class SpaceShipController: public Component{
our::Application* app;
Transform* T;
glm::vec3 x={0, 0, 0},y={0, 1, 0};
int lives=5;
int score=0;
//vector<Bullet*> bulletsVector;
MeshRenderer* bulletRendererr;
Sound* bulletSound;
Sound* killSound;
//int bulletID;//this will be count for all bullets generated

public:
    SpaceShipController(our::Application* application,Transform* Tran);
    void update(double delta_time,vector<Entity*>& entities);
    glm::vec3 Right();
    glm::vec3 Left();
    glm::vec3 Up();
    glm::vec3 Down();
    void setLives(int l);
    void setScore(int s);
    void setBulletSound(const char* fileName,bool loop);
    void setKillSound(const char* fileName,bool loop);
    int getLives();
    int getScore();
    void GenerateBullet(glm::vec3 position,vector<Entity*>& entities);
    //vector<Bullet*> getPointerToBulletsVector();
    void setBulletRenderer(MeshRenderer* r);
    void motionOfBullets(vector<Entity*>& entities);
};


