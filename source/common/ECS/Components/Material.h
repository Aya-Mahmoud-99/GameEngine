//
// Created by Aya on 12/12/2020.
//

#ifndef GFX_LAB_MATERIAL_H
#define GFX_LAB_MATERIAL_H
#include "./shader.hpp"

class Material {
    our::ShaderProgram* P;
public:
    Material(our::ShaderProgram* P);
    our::ShaderProgram* getPointerToProgram();

};


#endif //GFX_LAB_MATERIAL_H
