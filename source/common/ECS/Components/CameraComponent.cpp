//
// Created by Aya on 11/30/2020.
//

#include "CameraComponent.h"
//#include "Transform.h"
#include <iostream>

#include"Camera.h"

// Allows you to control the camera freely in world space

CameraController::CameraController(our::Application* application, Camera* cameraParam,Transform* Tr){
    ////fe 7aga fel world
    this->T=Tr;
    /// aya
    glm::mat4 mat=T->getMatrix();
    /*std::cout<<" "<<mat[0][0]<<" "<<mat[0][1]<<" "<<mat[0][2]<<" "<<mat[0][3]<<std::endl;
    std::cout<<" "<<mat[1][0]<<" "<<mat[1][1]<<" "<<mat[1][2]<<" "<<mat[1][3]<<std::endl;
    std::cout<<" "<<mat[2][0]<<" "<<mat[2][1]<<" "<<mat[2][2]<<" "<<mat[2][3]<<std::endl;
    std::cout<<" "<<mat[3][0]<<" "<<mat[3][1]<<" "<<mat[3][2]<<" "<<mat[3][3]<<std::endl;*/
    this->setEyeUpDirection(Tr->getMatrix());
    ///  aya
    this->app=application;
    this->camera=cameraParam;
    this->yaw_sensitivity = pitch_sensitivity = 0.01f;
    this->position_sensitivity = {3.0f, 3.0f, 3.0f};
    this->fov_sensitivity = glm::pi<float>()/10;
    this->distance_sensitivity = 2.0f;
    //this->position =getEye();
    //auto direction1 = getDirection();
    yaw = glm::atan(-direction.z, direction.x);
    float base_length = glm::sqrt(direction.x * direction.x + direction.z * direction.z);
    pitch = glm::atan(direction.y, base_length);
    this->origin = {0,0,0};
}

void CameraController::release(){
    if(mouse_locked) {
        mouse_locked = false;
        app->getMouse().unlockMouse(app->getWindow());
    }
}

void CameraController::update(double delta_time){
    if(app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && !mouse_locked){
        app->getMouse().lockMouse(app->getWindow());
        mouse_locked = true;
    } else if(!app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && mouse_locked) {
        app->getMouse().unlockMouse(app->getWindow());
        mouse_locked = false;
    }

    if(app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1)){
        glm::vec2 delta = app->getMouse().getMouseDelta();
        pitch -= delta.y * pitch_sensitivity;
        yaw -= delta.x * yaw_sensitivity;
    }

    if(pitch < -glm::half_pi<float>() * 0.99f) pitch = -glm::half_pi<float>() * 0.99f;
    if(pitch >  glm::half_pi<float>() * 0.99f) pitch  = glm::half_pi<float>() * 0.99f;
    yaw = glm::wrapAngle(yaw);

    float fov = camera->getVerticalFieldOfView() + app->getMouse().getScrollOffset().y * fov_sensitivity;
    fov = glm::clamp(fov, glm::pi<float>() * 0.01f, glm::pi<float>() * 0.99f);
    camera->setVerticalFieldOfView(fov);


    glm::vec3 current_sensitivity = this->position_sensitivity;
    if(app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT)) current_sensitivity *= speedup_factor;
    // and Aya
    glm::mat4 mat=T->getMatrix();
    glm::vec3 front = Forward(), up = Up(), right = Right();

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(app->getKeyboard().isPressed(GLFW_KEY_W)) this->eye += front * ((float)delta_time * current_sensitivity.z);
    if(app->getKeyboard().isPressed(GLFW_KEY_S)) this->eye -= front * ((float)delta_time * current_sensitivity.z);
    if(app->getKeyboard().isPressed(GLFW_KEY_Q)) this->eye += up * ((float)delta_time * current_sensitivity.y);
    if(app->getKeyboard().isPressed(GLFW_KEY_E)) this->eye -= up * ((float)delta_time * current_sensitivity.y);
    if(app->getKeyboard().isPressed(GLFW_KEY_D)) this->eye += right * ((float)delta_time * current_sensitivity.x);
    if(app->getKeyboard().isPressed(GLFW_KEY_A)) this->eye -= right * ((float)delta_time * current_sensitivity.x);
    /*if(app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && !mouse_locked){
        app->getMouse().lockMouse(app->getWindow());
        mouse_locked = true;
    } else if(!app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && mouse_locked) {
        app->getMouse().unlockMouse(app->getWindow());
        mouse_locked = false;
    }*/

    if(app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1)){
        glm::vec2 delta = app->getMouse().getMouseDelta();
        pitch += delta.y * pitch_sensitivity;
        yaw += delta.x * yaw_sensitivity;
    }

    if(pitch < -glm::half_pi<float>() * 0.99f) pitch = -glm::half_pi<float>() * 0.99f;
    if(pitch >  glm::half_pi<float>() * 0.99f) pitch  = glm::half_pi<float>() * 0.99f;
    yaw = glm::wrapAngle(yaw);

    distance += (float)app->getMouse().getScrollOffset().y * distance_sensitivity;
    if(distance < 0) distance = 0;

    //this->setEyePosition(origin + distance * (glm::vec3(glm::cos(yaw), 0, -glm::sin(yaw)) * glm::cos(pitch) + glm::vec3(0, glm::sin(pitch), 0)));
    //this->setTarget(origin);
    mat[3][0]=this->eye[0];
    mat[3][1]=this->eye[1];
    mat[3][2]=this->eye[2];

    this->setEyeUpDirection(mat);
    /// and Aya
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

[[nodiscard]] float CameraController::getYaw() const {return yaw;}
[[nodiscard]] float CameraController::getPitch() const {return pitch;}
[[nodiscard]] glm::vec3 CameraController::getPosition() const {return position;}

[[nodiscard]] float CameraController::getYawSensitivity() const {return yaw_sensitivity;}
[[nodiscard]] float CameraController::getPitchSensitivity() const {return pitch_sensitivity;}
[[nodiscard]] float CameraController::getFieldOfViewSensitivity() const {return fov_sensitivity;}
[[nodiscard]] glm::vec3 CameraController::getPositionSensitivity() const {return position_sensitivity;}
[[nodiscard]] float CameraController::getSpeedUpFactor() const {return speedup_factor;}

void CameraController::setYaw(float _yaw){
    this->yaw = glm::wrapAngle(_yaw);
}
void CameraController::setPitch(float _pitch){
    const float v = 0.99f*glm::pi<float>()/2;
    if(_pitch > v) _pitch = v;
    else if(_pitch < -v) _pitch = -v;
    this->pitch = _pitch;
}
void CameraController::setPosition(glm::vec3 _pos){
    this->position = _pos;
}

void CameraController::setYawSensitivity(float sensitivity){this->yaw_sensitivity = sensitivity;}
void CameraController::setPitchSensitivity(float sensitivity){this->pitch_sensitivity = sensitivity;}
void CameraController::setFieldOfViewSensitivity(float sensitivity){this->fov_sensitivity = sensitivity;}
void CameraController::setPositionSensitivity(glm::vec3 sensitivity){this->position_sensitivity = sensitivity;}
void CameraController::setEyeUpDirection(glm::mat4 mat){
  /*  glm::vec4 pos{0,0,0,1};
    pos=mat*pos;
    std::cout<<mat[0][0];
    this->eye={pos[0], pos[1], pos[2]};
    this->up={mat[0][1], mat[1][1], mat[2][1]};
    this->direction={mat[0][2], mat[1][2], mat[2][2]};*/
 /* glm::vec4 pos={}
   this->eye={0,0, 1};
    this->up={0.707,0.707,0};
    this->direction={0,0,-1};
    glm::vec4 pos={0,0,0,1};
    pos=mat*pos;
    glm::vec4 dir={0,0,-1,0};
    dir=mat*dir;
    glm::vec4 up={0,1,0,0};
    up=mat*up;*/
    this->eye={mat[3][0],mat[3][1],mat[3][2]};
    std::cout<<" "<<eye[0]<<" "<<eye[1]<<" "<<eye[2]<<std::endl;
    this->up={mat[1][0],mat[1][1],mat[1][2]};
    this->direction={mat[2][0],mat[2][1],-mat[2][2]};
}
glm::vec3 CameraController::getEye(){
    return eye;
}
glm::vec3 CameraController::getUp(){
    return up;
}
glm::vec3 CameraController::getDirection(){
    return direction;
}
glm::mat4 CameraController::getViewMatrix(){
    this->V=glm::mat4(1.0);
 /*   if(camera->dirtyFlags & camera->V_DIRTY){ // Only regenerate the view matrix if its flag is dirty
        V = glm::lookAt(eye, eye + direction, up);
        camera->dirtyFlags &= ~camera->V_DIRTY; // V is no longer dirty
    }*/
    this->V = glm::lookAt(eye, eye + direction, up);
    return V;
}
void CameraController::setTransform(Transform* Tr){
    this->T=Tr;
}
glm::vec3 CameraController::Right(){
    getViewMatrix();
    return {this->V[0][0],this->V[1][0],this->V[2][0]};
}
glm::vec3 CameraController::Left(){
    getViewMatrix();
    return {-this->V[0][0],-this->V[1][0],-this->V[2][0]};
}
glm::vec3 CameraController::Up(){
    getViewMatrix();
    return {this->V[0][1],this->V[1][1],this->V[2][1]};
}
glm::vec3 CameraController::Down(){
    getViewMatrix();
    return {-this->V[0][1],-this->V[1][1],-this->V[2][1]};
}
glm::vec3 CameraController::Forward(){
    getViewMatrix();
    return {-this->V[0][2],-this->V[1][2],-this->V[2][2]};
}
glm::vec3 CameraController::Backward(){
    getViewMatrix();
    return {this->V[0][2],this->V[1][2],this->V[2][2]};
}
void CameraController::setEyePosition(glm::vec3 eye){
        this->eye = eye;

}
void CameraController::setTarget(glm::vec3 target){
    glm::vec3 direction = target - eye;
        this->direction = direction;
}