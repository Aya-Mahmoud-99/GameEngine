//
// Created by Aya on 11/18/2020.
//

#include "Transform.h"
Transform::Transform(glm::vec3 t, glm::vec3 r, glm::vec3 s,Entity*p) {
    translation = t;
    rotation = r;
    scale=s;
    parent=p;
}
glm::mat4 Transform::to_mat4() const {
    return glm::translate(glm::mat4(1.0f), translation) *
           glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
           glm::scale(glm::mat4(1.0f), scale);
}
Entity* Transform::getParent(){
    return parent;
};