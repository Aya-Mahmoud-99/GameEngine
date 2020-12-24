//
// Created by Aya on 12/12/2020.
//

#ifndef GFX_LAB_MATERIAL_H
#define GFX_LAB_MATERIAL_H
#include "./shader.hpp"
#include "../Texture.h"
#include "../Sampler.h"
#include "../RenderState.h"
#include <any>

class Material {
    our::ShaderProgram* P;
    std::map<std::string, std::any> uniforms;
    Texture* pointerToTexture;
    Sampler* pointerToSampler;
    RenderState* pointerToRenderState;
public:
    Material(our::ShaderProgram* P);
    void setPointerToTexture(Texture* t);
    void setPointerToSampler(Sampler* s);
    void setPointerToRenderState(RenderState* rs);

    Texture* getPointerToTexture();
    Sampler* getPointerToSampler();
    RenderState* getPointerToRenderState();
    our::ShaderProgram* getPointerToProgram();
    void addUniform(std::string key,std::any value);
    std::any getUniform(std::string key);
    std::map<std::string, std::any> getUniforms();
};


#endif //GFX_LAB_MATERIAL_H
