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