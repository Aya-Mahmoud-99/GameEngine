//
// Created by BasantLoay on 12/24/2020.
//

#ifndef GFX_LAB_RENDERSTATE_H
#define GFX_LAB_RENDERSTATE_H
#include <glad/gl.h>
#include <glm/gtx/euler_angles.hpp>
#include <../common/application.hpp>

class RenderState{
    // Depth testing
    bool enable_depth_test ;
    GLenum depth_function ;
    float clear_depth = 1.0f;
    bool depth_mask = true;
    glm::bvec4 color_mask = {true, true, true, true};
    // Culling
    bool enable_face_culling ;
    GLenum culled_face ;
    GLenum front_face_winding ;
    // Blending
    bool enable_blending ;
    GLenum blend_equation ;
    GLenum blend_source_factor;
    GLenum blend_destination_factor ;
    glm::vec4 blend_constant_color = {1.0f,1.0f,1.0f,1.0f};

    public:
    RenderState(bool depthEnable=false,GLenum dpFun=GL_LEQUAL,bool cullEnable=false,GLenum cullface=GL_BACK,GLenum frontwinding=GL_CCW,bool blendEnable=false,GLenum blendFun=GL_FUNC_ADD,GLenum source=GL_SRC_ALPHA,GLenum dest=GL_ONE_MINUS_SRC_ALPHA);
    void DepthTesting();
    void Culling();
    void Blending();
    our::WindowConfiguration getWindowConfiguration();
    ~RenderState(){}
};

#endif //GFX_LAB_RENDERSTATE_H
