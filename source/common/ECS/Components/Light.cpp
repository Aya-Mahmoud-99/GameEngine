//
// Created by Aya on 12/18/2020.
//

#include "Light.h"
#include<iostream>
using namespace std;
LightComponent::LightComponent(Light Newlight,Transform *Trans,Camera*cam,CameraController*camCon){
    cout<<"light"<<Newlight.spot_angle.inner<<endl;
    //to be transfered to the OnEnter//////////////////////////////////////////////////// send these data in onEnter
    /*light.type = LightType::DIRECTIONAL;
    light.enabled = true;
    light.diffuse = {1,1,1};
    light.specular = {1,1,1};
    light.ambient = {0.1f, 0.1f, 0.1f};
    light.direction = {-1, -1, -1};
    light.position = {0, 1, 5};
    light.attenuation = {0, 0, 1};
    light.spot_angle = {glm::pi<float>()/4, glm::pi<float>()/2};
     ///////////////////////////////////////////////////////////////
    light.type = LightType::POINT;
    ///////////////////////////////////////////////////////////////////
    light.type = LightType::SPOT;
    light.direction = {0, 0, 1};
    light.position = {0, 1, -2};
     /////////////////////////////////////////////////////////////////
   *//////////////////////////////////////////////////////////////////////////////////////////
    this->light=Newlight;
    this->T=Trans;
    this->camera=cam;
    this->camera_controller=camCon;
}
void LightComponent::lightSelect(our::ShaderProgram* program,std::string prefix){
    /////////////////////////////////the position and direction will be retrieved from the transform component.
    setPosition();
    setDirection();
    //for(const auto& light : lights) {
  /*  program.set("light.diffuse", light.diffuse);
    program.set("light.specular", light.specular);
    program.set("light.ambient", light.ambient);
    // Some properties are only available in some light types
    switch(light.type){
        case LightType::DIRECTIONAL:
            program.set("light.direction", glm::normalize(light.direction));
            break;
        case LightType::POINT:
            program.set("light.position", light.position);
            program.set("light.attenuation_constant", light.attenuation.constant);
            program.set("light.attenuation_linear", light.attenuation.linear);
            program.set("light.attenuation_quadratic", light.attenuation.quadratic);
            break;
        case LightType::SPOT:
            program.set("light.position", light.position);
            program.set("light.direction", glm::normalize(light.direction));
            program.set("light.attenuation_constant", light.attenuation.constant);
            program.set("light.attenuation_linear", light.attenuation.linear);
            program.set("light.attenuation_quadratic", light.attenuation.quadratic);
            program.set("light.inner_angle", light.spot_angle.inner);
            program.set("light.outer_angle", light.spot_angle.outer);
            break;
    }*/
    program->set(prefix + "type", static_cast<int>(light.type));
    //cout<<static_cast<int>(light.type)<<endl;
    program->set(prefix + "color", light.color);
    //cout<<light.color[0]<<endl;
   // cout<<light.position[2]<<endl;
    //cout<<light.direction[2]<<endl;
    switch (light.type) {
        case LightType::DIRECTIONAL:
          //  cout<<"directional"<<endl;
            program->set(prefix + "direction", glm::normalize(light.direction));
            break;
        case LightType::POINT:
        //    cout<<"point"<<endl;
            program->set(prefix + "position", light.position);
            program->set(prefix + "attenuation_constant", light.attenuation.constant);
            program->set(prefix + "attenuation_linear", light.attenuation.linear);
            program->set(prefix + "attenuation_quadratic", light.attenuation.quadratic);
            break;
        case LightType::SPOT:
      //      cout<<"spot"<<endl;
            program->set(prefix + "position", light.position);
            program->set(prefix + "direction", glm::normalize(light.direction));
            program->set(prefix + "attenuation_constant", light.attenuation.constant);
            program->set(prefix + "attenuation_linear", light.attenuation.linear);
            program->set(prefix + "attenuation_quadratic", light.attenuation.quadratic);
            program->set(prefix + "inner_angle", light.spot_angle.inner);
            program->set(prefix + "outer_angle", light.spot_angle.outer);
            break;
    }
        //light_index++;
        //if(light_index >= MAX_LIGHT_COUNT) return;
    //}
}
our::WindowConfiguration LightComponent::getWindowConfiguration(){
    return { "Light", {1280, 720}, false };
}

void LightComponent::setPosition(){
    glm::mat4 mat=this->T->getMatrix();
    this->light.position={mat[3][0],mat[3][1],mat[3][2]};
}
void LightComponent::setDirection(){
    glm::mat4 mat=this->T->getMatrix();
    this->light.direction={mat[2][0],mat[2][1],-mat[2][2]};
}
glm::vec3 LightComponent::getPosition(){
    return this->light.position;
}
glm::vec3 LightComponent::getDirection(){
    return this->light.direction;
}