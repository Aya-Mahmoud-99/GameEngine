//
// Created by Aya on 12/18/2020.
//

#include "Texture.h"
Texture::Texture(){

    {
        // Here we generate single texture
        glGenTextures(1, &texture);
        uint8_t pixel_data[] = {
                255,   0,   0, 255,
                0, 255,   0, 255,
                0,   0, 255, 255,
                255, 255,   0, 255,
        };
        // To work with our texture as a 2D texture, we bind it to GL_TEXTURE_2D.
        glBindTexture(GL_TEXTURE_2D, texture);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    // Store the texture name in the dictionary
    textures["colors"] = texture;

    {
        glGenTextures(1, &texture);
        // Here, we are creating a local type alias for our color vector which is a specialization of glm vector with 4 uint8 components.
        using color = glm::vec<4, glm::uint8, glm::defaultp>;
        // Then we define some constant colors to use later.
        const color W = {255, 255, 255, 255}, Y = {255, 255, 0, 255},
                B = {0, 0, 0, 255};
        // Instead of using the data type uint8 and writing each component in the array separately, we use our color data type so each element will be a full color.
        color pixel_data[] = {
                W, W, Y, Y, Y, Y, W, W,
                W, Y, Y, B, B, Y, Y, W,
                Y, Y, B, Y, Y, B, Y, Y,
                Y, Y, Y, Y, Y, Y, Y, Y,
                Y, Y, B, Y, Y, B, Y, Y,
                Y, Y, B, Y, Y, B, Y, Y,
                W, Y, Y, Y, Y, Y, Y, W,
                W, W, Y, Y, Y, Y, W, W,
        };
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        // Note that we still used GL_UNSIGNED_BYTE because each component is still a uint8.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    textures["smiley"] = texture;

    {
        glGenTextures(1, &texture);
        // Here we define another local type alias for the color but with 3 components (RGB) instead of 4 (RGBA).
        using color = glm::vec<3, glm::uint8, glm::defaultp>;
        // The colors here has no alpha.
        const color W = {255, 255, 255}, R = {255, 0, 0};
        color pixel_data[] = {
                W, W, W, W, W,
                W, W, R, W, W,
                W, R, R, R, W,
                W, W, R, W, W,
                W, W, W, W, W,
        };
        glBindTexture(GL_TEXTURE_2D, texture);
        // Here we must use an alignment of 1 since each row has odd number of bytes.
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        // Since we have no alpha, the internal format is GL_RGB8 and the format is GL_RGB.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 5, 5, 0, GL_RGB, GL_UNSIGNED_BYTE, pixel_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    textures["cross"] = texture;

    {
        glGenTextures(1, &texture);
        const GLuint width = 256, height = 128, tile_size = 32;
        // In this texture, we will store floats instead of bytes.
        float pixel_data[width * height];
        GLuint index = 0;
        // This loop will create a bubble shaped texture.
        for(GLuint y = 0; y < height; ++y){
            for(GLuint x = 0; x < width; ++x){
                auto tile_coord = 2.0f * glm::fract(glm::vec2(x,y)/static_cast<float>(tile_size)) - 1.0f;
                auto length2 = glm::dot(tile_coord, tile_coord);
                pixel_data[index++] = length2 > 1 ? 0.0f : glm::sqrt(1.0f - length2);
            }
        }
        glBindTexture(GL_TEXTURE_2D, texture);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, pixel_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    textures["bubbles"] = texture;

    // The remaining textures are read from files using our function that internally uses the "stb_image" library to read the color data from the files.
    glGenTextures(1, &texture);
    our::texture_utils::loadImage(texture, "assets/Textures/color-grid.png");
    textures["color-grid"] = texture;

    glGenTextures(1, &texture);
    our::texture_utils::loadImage(texture, "assets/Textures/moon.jpg");
    textures["moon"] = texture;

    glGenTextures(1, &texture);
    our::texture_utils::loadImage(texture, "assets/Textures/monarch.png");
    textures["monarch"] = texture;

    current_texture_name = "color-grid";

    glClearColor(0, 0, 0, 1);
}
our::WindowConfiguration Texture::getWindowConfiguration() {
return { "Textures", {1280, 720}, false };}

void Texture::TextureUpdate(){
    texture = textures[current_texture_name];
    // Unlike other uniforms, we send textures in a special manner.
// First, we sst the active texture unit. Here, we pick unit 0 which is actually the active unit by default but we still wrote this line for demonstration.
    glActiveTexture(GL_TEXTURE0);
// When we bind the texture, we also bind it to the active unit. So this texture is now bound to unit 0.
    glBindTexture(GL_TEXTURE_2D, texture);
}


