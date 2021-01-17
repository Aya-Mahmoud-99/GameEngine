//
// Created by BasantLoay on 1/15/2021.
//

#ifndef GFX_LAB_BULLET_H
#define GFX_LAB_BULLET_H
#pragma once
#include "Entity.h"
#include"Sound.h"

class Bullet : public Entity{
public:
    int ID;
    Bullet(glm::vec3 pos);
    int moveBullet(int index,vector<Entity*>& entities,Sound* s);
    bool collideBullet(int index,vector<Entity*>& entities,Sound* s);
    ~Bullet(){}
};

#endif //GFX_LAB_BULLET_H
