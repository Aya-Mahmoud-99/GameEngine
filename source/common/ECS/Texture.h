//
// Created by Aya on 12/18/2020.
//

#ifndef GFX_LAB_TEXTURE_H
#define GFX_LAB_TEXTURE_H
#include <texture/texture-utils.h>
#include <unordered_map>
#include "./shader.hpp"
#include <../common/application.hpp>
//#include <imgui-utils/utils.hpp>
class Texture {
    GLuint texture;
    our::ShaderProgram program;
    GLuint vertex_array = 0;

    // Since we will have multiple textures in our scene, we will store them in a dictionary
    // and select one to display by its key.
    // Note that textures are OpenGL objects so we identify them via a GLuint.
    std::unordered_map<std::string, GLuint> textures;
    std::string current_texture_name;
    // This integer defines the mip level that we will display.
    int level_of_detail = 0;
    // This will be used to zoom into the texture since they can become very small at high mip levels.
    float zoom = 1;
    Texture();
    void TextureUpdate();
    our::WindowConfiguration getWindowConfiguration();
};


#endif //GFX_LAB_TEXTURE_H
