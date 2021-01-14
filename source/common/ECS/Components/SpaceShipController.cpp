//
// Created by Aya on 1/13/2021.
//

#include "SpaceShipController.h"

SpaceShipController::SpaceShipController(our::Application* application,Transform* Tran){
app=application;
T=Tran;
glm::mat4 mat=T->getMatrix();
x= {mat[3][0],mat[3][1],mat[3][2]};
//y={mat[1][0],mat[1][1],mat[1][2]};
}
void SpaceShipController::update(double delta_time){


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
    //if(app->getKeyboard().isPressed(GLFW_KEY_ENTER)) GenerateBullet(x);
    mat[3][0]=x[0];
    mat[3][1]=x[1];
    mat[3][2]=x[2];
  //  std::cout<<"SpaceShipController after changing \n";
  //  std::cout<<x[0]<<" "<<x[1]<<" "<<x[2]<<" \n";
    //mat[1][0]=y[0];
    //mat[1][1]=y[1];
    //mat[1][2]=y[2];
    T->setMatrix(mat);

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
void SpaceShipController::GenerateBullet(glm::vec3 position){
//create new instance from bullet class
//given x in position[0], y in position[1] but increment y alittle bit to see the bullet above the spaceship

}