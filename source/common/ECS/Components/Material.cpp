//
// Created by Aya on 12/12/2020.
//

#include "Material.h"
Material::Material(our::ShaderProgram* p){
    P=p;
}
our::ShaderProgram * Material::getPointerToProgram() {
    return P;
}
void Material::addUniform(std::string key,std::any value){
    uniforms[key]=value;
};
std::any Material::getUniform(std::string key){
    return uniforms[key];
};
std::map<std::string, std::any> Material::getUniforms(){
    return uniforms;
};
Sampler* Material::getPointerToSampler() {
    return pointerToSampler;
}
Texture * Material::getPointerToAlbedoMap() {
    return albedo_map;
}
Texture * Material::getPointerToAmbientOcuulsionMap() {
    return ambient_occlusion_map;
}
Texture * Material::getPointerToEmissiveMap() {
    return emissive_map;
}

Texture * Material::getPointerToRoughnessMap() {
    return roughness_map;
}
Texture * Material::getPointerToSpecularMap() {
    return specular_map;
}
void Material::setPointerToAlbedoMap(Texture *t) {
    albedo_map=t;
}
void Material::setPointerToAmbientOcuulsionMap(Texture *t) {
    ambient_occlusion_map=t;
}
void Material::setPointerToEmissiveMap(Texture *t) {
    emissive_map=t;
}
void Material::setPointerToRoughnessMap(Texture *t) {
    roughness_map=t;
}
void Material::setPointerToSpecularMap(Texture *t) {
    specular_map=t;
}
RenderState* Material::getPointerToRenderState(){
    return pointerToRenderState;
}
void Material::setPointerToSampler(Sampler *s) {
    pointerToSampler=s;
}

void Material::setPointerToRenderState(RenderState* rs){
    pointerToRenderState=rs;
}