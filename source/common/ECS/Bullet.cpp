//
// Created by BasantLoay on 1/15/2021.
//

#include "Bullet.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"
#include "Components/Light.h"

Bullet::Bullet(glm::vec3 pos) {

    Transform* t=new Transform(pos+glm::vec3{0,+1,0},glm::vec3{0,0,0},glm::vec3{0.4,0.3,0.4});
    addComponent(t);
    this->setEntityName("bullet");
}
int Bullet::moveBullet(int index,vector<Entity*>& entities,Sound* s)
{
    bool flag =this->collideBullet(index,entities,s);
    if(flag)
        return 1;
    glm::vec3 currentPosition = this->getComponent<Transform>()->getPosition();
    this->getComponent<Transform>()->setPosition(currentPosition+glm::vec3{0,+0.3,0});
    return 0;
}
bool Bullet::collideBullet(int index,vector<Entity*>& entities,Sound* s)
{
    //vector<Entity*>::iterator bullet=entities.;
    glm::vec3 posBullet=this->getComponent<Transform>()->getPosition();

    for(int i=0;i<entities.size();i++)
    {
        glm::vec3 pos=entities.at(i)->getComponent<Transform>()->getPosition();
        if(entities.at(i)&&entities.at(i)->getEntityName()=="chicken"&& abs(pos.x-posBullet.x)<1 &&abs(pos.y-posBullet.y)<2.5)// &&  abs(pos.z-posBullet.z)<2.5)
        {
            s->play();
            entities.erase(entities.begin()+index);
            if(index>i)
                entities.erase(entities.begin()+i);//remove chicken
            else
                entities.erase(entities.begin()+i-1);

            return true;
        }
    }
    return false;
}