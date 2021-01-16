//
// Created by Aya on 11/17/2020.
//
#pragma once
#ifndef GFX_LAB_WORLD_H
#define GFX_LAB_WORLD_H
#include <glm/glm.hpp>
#include <ECS/Components/Transform.h>
#include <ECS/Components/SpaceShipController.h>
#include "vector"
#include <ECS/Components/MeshRenderer.h>
class Entity;
using namespace std;
struct MeshRendererTransform
{
    MeshRenderer* MR;
    glm::mat4 matrix;
};

class World {
vector<Entity*> Entities;
MeshRenderer* bulletRenderer;
MeshRenderer* EggRenderer;
public:

    Entity* createEntity(Entity* e);
    //void assignComponentToEntity(Entity* e,Component* c);
    vector<Entity*>& getEntities();
    void Rendering();
    void RenderingSystem();
    glm::mat4 getCameraEntityTransform();
    Entity* getCameraEntity();
    Entity* getLightEntity();
    void getTagEntities(vector<Entity*>& entities,string tag);
    void generateEggs();
    Entity* getSpaceShipEntity();
    void moveEggs();
    void LoadEgg();
    void deleteNullObjects();
    void deleteEggsOnGround();
    void setBulletRenderer(Texture*t,our::Mesh*m,our::ShaderProgram*p);
    MeshRenderer* getBulletRenderer();
    ~World();
};


#endif //GFX_LAB_WORLD_H
