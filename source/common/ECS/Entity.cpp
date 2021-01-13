//
// Created by Aya on 11/17/2020.
//

#include "Entity.h"
//#include "Component.h"

void Entity::addComponent(Component *c) {
    //c=new Component();
    components.push_back(c);
}
void Entity::removeComponent(Component *c) {
    for(int i=0;i<components.size();i++){
        //delete components[i];
        if(components[i]==c)components.erase(components.begin()+i);
    }
}
vector<Component*>& Entity::getComponents() {
return components;
}
string Entity::getEntityName(){
    return Name;
}
void Entity::setEntityName(string n){
    Name=n;
}
/*
template<typename T>
T* Entity::getComponent(){
T* t = nullptr;
for (auto i : components) {
if ((t = dynamic_cast<T*>(i)) != nullptr) return t;
}

return NULL;
}
 */
/*Entity::~Entity() {
    for(int i=0;i<components.size();i++){
        delete components[i];
    }
}*/