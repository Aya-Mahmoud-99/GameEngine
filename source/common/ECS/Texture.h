//
// Created by Aya on 12/18/2020.
//

#ifndef GFX_LAB_TEXTURE_H
#define GFX_LAB_TEXTURE_H
#include <texture/texture-utils.h>
#include <unordered_map>
#include "./shader.hpp"
#include <../common/application.hpp>

#include "../texture/texture-utils.h"
class Texture {
    GLuint texture;
    //our::ShaderProgram program;
    //GLuint vertex_array = 0;

    //std::unordered_map<std::string, GLuint> textures;
    //std::string current_texture_name;
    // This integer defines the mip level that we will display.
    //int level_of_detail = 0;
    // This will be used to zoom into the texture since they can become very small at high mip levels.
    //float zoom = 1;
    Texture(const char * ImagePath);
    void TextureBind();
    ~Texture();

    our::WindowConfiguration getWindowConfiguration();
};


#endif //GFX_LAB_TEXTURE_H
