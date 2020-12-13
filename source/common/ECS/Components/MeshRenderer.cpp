//
// Created by Aya on 11/18/2020.
//

#include "MeshRenderer.h"
MeshRenderer::MeshRenderer(our::Mesh* m,Material* mat){
    mesh=m;
    material=mat;
    //program=p;
}
our::Mesh* MeshRenderer::getPointerToMesh() {
    return mesh;
}
Material * MeshRenderer::getMaterial() {
    return material;
}
/*our::ShaderProgram* MeshRenderer::getPointerToProgram() {
    return program;
}*/
/*MeshRenderer::~MeshRenderer() {
    delete mesh;
    delete program;///\\get modified
}*/