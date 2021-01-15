//
// Created by Aya on 11/17/2020.
//
//#include <string>
#include "Component.h"
#include <string>
#include "vector"
using namespace std;
//#ifndef GFX_LAB_ENTITY_H
//#define GFX_LAB_ENTITY_H

//class Component;
class Entity {
string Name;
vector<Component*> components;
int tag;
bool collided;
int counter;
public:
    void addComponent(Component* c);
    void removeComponent(Component* c);
    template<typename T>
    T* getComponent(){
    T* t = nullptr;
    for (auto i : components) {
        if ((t = dynamic_cast<T*>(i)) != nullptr) return t;
    }

    return NULL;
};
    string getEntityName();
    void setEntityName(string n);
    void setCollided(bool isCollided);
    bool getCollided();
    vector<Component*>& getComponents();
    void setCounter(int count);
    int getCounter();
~Entity(){
    collided=false;
    counter=0;

};
};


