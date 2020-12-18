//
// Created by Aya on 12/18/2020.
//

#include <memory>
#include"ECS/Component.h"
#include"Camera.h"
#include "CameraComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <../common/application.hpp>
#include "Transform.h"
#include <unordered_map>
#include "./shader.hpp" //////////////////////////////////
#include <mesh/mesh-utils.hpp>////////////////////
#include <mesh/common-vertex-types.hpp>//////////////////////////////////
#include <mesh/common-vertex-attributes.hpp>////////////////////////////////////////////////////
enum class LightType {
    DIRECTIONAL,
    POINT,
    SPOT
};
struct Light {
// Here we define our light. First member specifies its type.
    LightType type;
    bool enabled;
// We also define the color & intensity of the light for each component of the Phong model (Ambient, Diffuse, Specular).
    glm::vec3 diffuse, specular, ambient;
    glm::vec3 position; // Used for Point and Spot Lights only
    glm::vec3 direction; // Used for Directional and Spot Lights only
// This affects how the light will dim out as we go further from the light.
// The formula is light_received = light_emitted / (a*d^2 + b*d + c) where a, b, c are the quadratic, linear and constant factors respectively.
    struct {
        float constant, linear, quadratic;
    } attenuation; // Used for Point and Spot Lights only
// This specifies the inner and outer cone of the spot light.
// The light power is 0 outside the outer cone, the light power is full inside the inner cone.
// The light power is interpolated in between the inner and outer cone.
    struct {
        float inner, outer;
    } spot_angle; // Used for Spot Lights only

};
class LightComponent :public Component {
public:
    // We will create a different shader program for each light type.
    std::unordered_map<LightType, our::ShaderProgram> programs; //to be edited/////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::unordered_map<std::string, std::unique_ptr<our::Mesh>> meshes;
    Light light{};

    Transform *T;//////////////////////////////////////////
    Camera *camera;/////////////////////////////////////////////////////////////////////////
    CameraController *camera_controller;//////////////////////////////////////////////////////////////////

    std::vector<Light> lights;
    our::WindowConfiguration getWindowConfiguration() ;/////i removed overide world since it is not a virtyal function anymore
    LightComponent(Transform *Trans,Camera*cam=NULL,CameraController*camCon=NULL);
    void lightUpdate(int light_index,int MAX_LIGHT_COUNT,our::ShaderProgram program);
    void setPosition();
    void setDirection();
    glm::vec3 getPosition();
    glm::vec3 getDirection();
};