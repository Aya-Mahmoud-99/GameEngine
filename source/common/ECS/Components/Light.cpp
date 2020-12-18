//
// Created by Aya on 12/18/2020.
//

#include "Light.h"
LightComponent::LightComponent(Transform *Trans,Camera*cam,CameraController*camCon){
    Light light = {};
    light.type = LightType::DIRECTIONAL;
    light.enabled = true;
    light.diffuse = {1,1,1};
    light.specular = {1,1,1};
    light.ambient = {0.1f, 0.1f, 0.1f};
    light.direction = {-1, -1, -1};
    light.position = {0, 1, 5};
    light.attenuation = {0, 0, 1};
    light.spot_angle = {glm::pi<float>()/4, glm::pi<float>()/2};
    lights.push_back(light);
    light.type = LightType::POINT;
    lights.push_back(light);
    light.type = LightType::SPOT;
    light.direction = {0, 0, 1};
    light.position = {0, 1, -2};
    lights.push_back(light);

    this->T=Trans;
    this->camera=cam;
    this->camera_controller=camCon;
}
void LightComponent::lightUpdate(int light_index,int MAX_LIGHT_COUNT,our::ShaderProgram program){
    /////////////////////////////////the position and direction will be retrieved from the transform component.
    setPosition();
    setDirection();
    for(const auto& light : lights) {
        if(!light.enabled) continue;
        std::string prefix = "lights[" + std::to_string(light_index) + "].";

        program.set(prefix + "diffuse", light.diffuse);
        program.set(prefix + "specular", light.specular);
        program.set(prefix + "ambient", light.ambient);
        program.set(prefix + "type", static_cast<int>(light.type));


        switch (light.type) {
            case LightType::DIRECTIONAL:
                program.set(prefix + "direction", glm::normalize(light.direction));
                break;
            case LightType::POINT:
                program.set(prefix + "position", light.position);
                program.set(prefix + "attenuation_constant", light.attenuation.constant);
                program.set(prefix + "attenuation_linear", light.attenuation.linear);
                program.set(prefix + "attenuation_quadratic", light.attenuation.quadratic);
                break;
            case LightType::SPOT:
                program.set(prefix + "position", light.position);
                program.set(prefix + "direction", glm::normalize(light.direction));
                program.set(prefix + "attenuation_constant", light.attenuation.constant);
                program.set(prefix + "attenuation_linear", light.attenuation.linear);
                program.set(prefix + "attenuation_quadratic", light.attenuation.quadratic);
                program.set(prefix + "inner_angle", light.spot_angle.inner);
                program.set(prefix + "outer_angle", light.spot_angle.outer);
                break;
        }
        light_index++;
        if(light_index >= MAX_LIGHT_COUNT) break;
    }
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