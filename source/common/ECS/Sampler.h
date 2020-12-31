//
// Created by Aya on 12/18/2020.
//

#ifndef GFX_LAB_SAMPLER_H
#define GFX_LAB_SAMPLER_H
#include <memory>
#include <unordered_map>
#include "./shader.hpp"
#include <../common/application.hpp>
//#include <mesh/mesh-utils.hpp>////////////////////
//#include <mesh/common-vertex-types.hpp>//////////////////////////////////
//#include <mesh/common-vertex-attributes.hpp>////////////////////////////////////////////////////
//#include"Components/Camera.h"
//#include "Components/CameraComponent.h"
#include "Components/Transform.h"
class Sampler {
    //our::ShaderProgram program;

    //std::unordered_map<std::string, std::unique_ptr<our::Mesh>> meshes;

    //std::unordered_map<std::string, GLuint> textures;

    // Samplers are OpenGL objects so we identify them using a GLuint.
    GLuint sampler;

    // These sampling parameters will be stored in the Sampler object.
    GLenum magnification_filter = GL_LINEAR, minification_filter = GL_LINEAR_MIPMAP_LINEAR;
    GLenum wrap_s = GL_REPEAT, wrap_t = GL_REPEAT;
    glm::vec4 border_color = {1,1,1,1};
    GLfloat max_anisotropy = 1.0f;

    GLenum polygon_mode = GL_FILL;

    Transform *T;
    public:
    void SamplerBind(our::ShaderProgram *p,int unit);
    our::WindowConfiguration getWindowConfiguration();
    ~Sampler();

    Sampler(Transform *Trans=NULL);
};


#endif //GFX_LAB_SAMPLER_H
