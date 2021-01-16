//
// Created by BasantLoay on 1/15/2021.
//

#ifndef GFX_LAB_BULLET_H
#define GFX_LAB_BULLET_H
#pragma once
#include "Entity.h"

class Bullet : public Entity{
public:
    int ID;
    Bullet(glm::vec3 pos);
    void moveBullet(int index,vector<Entity*>& entities);
    bool collideBullet(int index,vector<Entity*>& entities);
    ~Bullet(){}
};

#endif //GFX_LAB_BULLET_H
