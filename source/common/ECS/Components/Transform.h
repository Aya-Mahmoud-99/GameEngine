//
// Created by Aya on 11/18/2020.
//
#include"ECS/Component.h"
#include <glm/gtx/euler_angles.hpp>
#ifndef GFX_LAB_TRANSFORM_H
#define GFX_LAB_TRANSFORM_H


class Transform: public Component{
    glm::vec3 translation, rotation, scale;
    Entity* parent;
    Transform(glm::vec3 translation={0,0,0} ,glm::vec3 rotation={0,0,0},glm::vec3 scale={0,0,0},Entity*parent= nullptr);
    glm::mat4 to_mat4() const;
    Entity* getParent();
};


#endif //GFX_LAB_TRANSFORM_H
