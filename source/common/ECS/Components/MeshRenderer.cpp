//
// Created by Aya on 11/18/2020.
//

#include "MeshRenderer.h"
MeshRenderer::MeshRenderer(our::Mesh* m,our::ShaderProgram* p){
    mesh=m;
    program=p;
}
our::Mesh* MeshRenderer::getPointerToMesh() {
    return mesh;
}
our::ShaderProgram* MeshRenderer::getPointerToProgram() {
    return program;
}
MeshRenderer::~MeshRenderer() {
    delete mesh;
    delete program;
}