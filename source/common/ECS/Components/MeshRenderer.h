//
// Created by Aya on 11/18/2020.
//
#include "../../Mesh/Mesh.hpp"
#include <shader.hpp>

#ifndef GFX_LAB_MESHRENDERER_H
#define GFX_LAB_MESHRENDERER_H


class MeshRenderer {
    our::Mesh* mesh;
    our::ShaderProgram* program;
    MeshRenderer(our::Mesh* mesh= nullptr,our::ShaderProgram* program= nullptr);
};


#endif //GFX_LAB_MESHRENDERER_H
