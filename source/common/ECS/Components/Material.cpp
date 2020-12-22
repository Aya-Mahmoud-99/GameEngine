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
Texture * Material::getPointerToTexture() {
    return pointerToTexture;
}
void Material::setPointerToSampler(Sampler *s) {
    pointerToSampler=s;
}
void Material::setPointerToTexture(Texture *t) {
    pointerToTexture=t;
}
