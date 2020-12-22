//
// Created by Aya on 12/18/2020.
//
#include <iostream>
#include "Texture.h"
Texture::Texture(const char * ImagePath){
    glGenTextures(1, &texture);
    our::texture_utils::loadImage(texture, ImagePath);

}
our::WindowConfiguration Texture::getWindowConfiguration() {
return { "Textures", {1280, 720}, false };}

void Texture::TextureBind(){
     glActiveTexture(GL_TEXTURE0);
// When we bind the texture, we also bind it to the active unit. So this texture is now bound to unit 0.
    glBindTexture(GL_TEXTURE_2D, texture);
}
Texture::~Texture(){
    glDeleteTextures(1, &texture);
}


