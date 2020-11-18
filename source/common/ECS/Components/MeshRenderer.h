//
// Created by Aya on 11/18/2020.
//
#include "../../Mesh/Mesh.hpp"
#include <shader.hpp>
#include"ECS/Component.h"

#ifndef GFX_LAB_MESHRENDERER_H
#define GFX_LAB_MESHRENDERER_H


class MeshRenderer : public Component{
    our::Mesh* mesh;
    our::ShaderProgram* program;
    MeshRenderer(our::Mesh* mesh= nullptr,our::ShaderProgram* program= nullptr);
    our::Mesh* getPointerToMesh();
    our::ShaderProgram* getPointerToProgram();
};


#endif //GFX_LAB_MESHRENDERER_H
