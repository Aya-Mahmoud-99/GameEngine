//
// Created by Aya on 1/13/2021.
//

#include "SpaceShipController.h"


SpaceShipController::SpaceShipController(our::Application* application,Transform* Tran){
app=application;
T=Tran;
glm::mat4 mat=T->getMatrix();
x= {mat[3][0],mat[3][1],mat[3][2]};
bulletID=1;
//y={mat[1][0],mat[1][1],mat[1][2]};
}
void SpaceShipController::update(double delta_time,vector<Entity*>& entities){


    glm::mat4 mat=T->getMatrix();
    x= {mat[3][0],mat[3][1],mat[3][2]};
 //   std::cout<<"SpaceShipController before changing \n";
 //   std::cout<<x[0]<<" "<<x[1]<<" "<<x[2]<<" \n";
    //y={mat[1][0],mat[1][1],mat[1][2]};
    glm::vec3 up = Up(), right = Right();

    if(app->getKeyboard().isPressed(GLFW_KEY_D) && x[0]<8) this->x += up * ((float)delta_time*100.0f);
    if(app->getKeyboard().isPressed(GLFW_KEY_A) && x[0]>-10) this->x -= up * ((float)delta_time *100.0f);
    if(app->getKeyboard().isPressed(GLFW_KEY_S) && x[1]>-7) this->x += right * ((float)delta_time*100.0f);
    if(app->getKeyboard().isPressed(GLFW_KEY_W) && x[1]< 1) this->x -= right * ((float)delta_time*100.0f);
    if(app->getKeyboard().justPressed(GLFW_KEY_SPACE) && lives >0) this->GenerateBullet(x, entities);
    //if(app->getKeyboard().isPressed(GLFW_KEY_ENTER)) GenerateBullet(x);
    mat[3][0]=x[0];
    mat[3][1]=x[1];
    mat[3][2]=x[2];
        T->setPosition(x);
  //  std::cout<<"SpaceShipController after changing \n";
  //  std::cout<<x[0]<<" "<<x[1]<<" "<<x[2]<<" \n";
    //mat[1][0]=y[0];
    //mat[1][1]=y[1];
    //mat[1][2]=y[2];
    //T->setMatrix(mat);

}
glm::vec3 SpaceShipController::Right(){
    glm::mat4 M=T->getMatrix();
    return {M[0][0],M[1][0],M[2][0]};
}
glm::vec3 SpaceShipController::Left(){
    glm::mat4 M=T->getMatrix();
    return {-M[0][0],-M[1][0],-M[2][0]};
}
glm::vec3 SpaceShipController::Up(){
    glm::mat4 M=T->getMatrix();
    return {M[0][1],M[1][1],M[2][1]};
}
glm::vec3 SpaceShipController::Down(){
    glm::mat4 M=T->getMatrix();
    return {-M[0][1],-M[1][1],-M[2][1]};
}
void SpaceShipController::GenerateBullet(glm::vec3 position,vector<Entity*>& entities){
//create new instance from bullet class
//given x in position[0], y in position[1] but increment y alittle bit to see the bullet above the spaceship
    Bullet* bptr=new Bullet(position);
    bptr->ID=bulletID++;
    bptr->addComponent(bulletRendererr);
    //this->bulletsVector.push_back(bptr);
    entities.push_back(bptr);
}
void SpaceShipController::setLives(int l){
    lives=l;
}
void SpaceShipController::setScore(int s){
    score=s;
}
int SpaceShipController::getLives(){
    return lives;
}
int SpaceShipController::getScore(){
    return score;
}

/*vector<Bullet*> SpaceShipController::getPointerToBulletsVector(){
    return bulletsVector;
}
*/
void SpaceShipController::setBulletRenderer(MeshRenderer* r){
    bulletRendererr=r;
}

void SpaceShipController::motionOfBullets(vector<Entity*>& entities){
    //vector<Bullet*>::iterator bullet;
    //bullet=bulletsVector.begin();
//    for(int j=0;j<bulletsVector.size();j++)
//    {
//        if(bulletsVector[j]->getComponent<Transform>()->getPosition().y>11)
//        {   int id=bulletsVector[j]->ID;
//            bulletsVector[j]=NULL;
//            bulletsVector.erase(bulletsVector.begin()+j);
            for(int i=0;i<entities.size();i++)
            {
                if(entities.at(i)&&entities.at(i)->getEntityName()=="bullet")//&& ((Bullet*)entities.at(i))->ID==id)
                {
                    if(entities.at(i)->getComponent<Transform>()->getPosition().y>12)
                        entities.erase(entities.begin()+i);
                    //delete bullet;
                    //bullet=NULL;
                    else
                        ((Bullet*)entities.at(i))->moveBullet(i,entities);
                }

            }

}