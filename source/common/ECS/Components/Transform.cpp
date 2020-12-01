//
// Created by Aya on 11/18/2020.
//
#include "..\Entity.h"
#include "Transform.h"
Transform::Transform(glm::vec3 t, glm::vec3 r, glm::vec3 s,Entity*p) {
    translation = t;
    rotation = r;
    scale=s;
    parent=p;
    V=to_mat4();
}
glm::mat4 Transform::to_mat4() {
    return glm::translate(glm::mat4(1.0f), translation) *
           glm::yawPitchRoll(rotation.y, rotation.x, rotation.z) *
           glm::scale(glm::mat4(1.0f), scale);
}
Entity* Transform::getParent(){
    return parent;
};
glm::mat4 Transform::CameraTransform(int num,float deltatime,float currentsenstivity) {
    //glm::mat4 V=this->to_mat4();
    //glm::mat4 V=curr
    if(num==0){ //forward//direction
        V[0][2]*=-1* (deltatime * currentsenstivity);
        V[1][2]*=-1* (deltatime * currentsenstivity);
        V[2][2]*=-1* (deltatime * currentsenstivity);
    }
    if(num==1){ //backward//direction
        V[0][2]*=(deltatime * currentsenstivity);
        V[1][2]*=(deltatime * currentsenstivity);
        V[2][2]*=(deltatime * currentsenstivity);

    }
    if(num==2){ //up//y
        V[0][1]*=(deltatime * currentsenstivity);
        V[1][1]*=(deltatime * currentsenstivity);
        V[2][1]*=(deltatime * currentsenstivity);

    }
    if(num==3){ //down//y
        V[0][1]*=-1*(deltatime * currentsenstivity);
        V[1][1]*=-1*(deltatime * currentsenstivity);
        V[2][1]*=-1*(deltatime * currentsenstivity);

    }
    if(num==4){ //right//x
        V[0][0]*=(deltatime * currentsenstivity);
        V[1][0]*=(deltatime * currentsenstivity);
        V[2][0]*=(deltatime * currentsenstivity);

    }
    if(num==5){ //left//x
        V[0][0]*=-1*(deltatime * currentsenstivity);
        V[1][0]*=-1*(deltatime * currentsenstivity);
        V[2][0]*=-1*(deltatime * currentsenstivity);
    }
    return V;
}
glm::mat4 Transform::parents_mat() {
    glm::mat4 matrix=V;
    Entity* temp=this->getParent();
        while (temp != NULL) {
            Transform *tempTransform = temp->getComponent<Transform>();
            matrix = matrix * tempTransform->V;
            temp = tempTransform->getParent();
        }
    return matrix;
}
