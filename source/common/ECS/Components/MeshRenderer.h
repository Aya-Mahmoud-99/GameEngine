//
// Created by Aya on 11/18/2020.
//
#include "Material.h"
#include "../../Mesh/Mesh.hpp"
//#include <shader.hpp>
#include"ECS/Component.h"

#ifndef GFX_LAB_MESHRENDERER_H
#define GFX_LAB_MESHRENDERER_H


class MeshRenderer : public Component{
    our::Mesh* mesh;
    //our::ShaderProgram* program;
    Material* material;
public:
    MeshRenderer(our::Mesh* mesh= nullptr,Material* material= nullptr);
    our::Mesh* getPointerToMesh();
    Material* getMaterial();
  //  our::ShaderProgram* getPointerToProgram();
    ~MeshRenderer(){

    };
};


#endif //GFX_LAB_MESHRENDERER_H
