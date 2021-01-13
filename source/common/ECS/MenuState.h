//
// Created by myass on 1/10/2021.
//

#ifndef GFX_LAB_MENUSTATE_H
#define GFX_LAB_MENUSTATE_H

#endif //GFX_LAB_MENUSTATE_H


#include "GameState.h"

class MenuState : public GameState{

private:
    // CameraController* PointerToCamController;
    std::vector<Light> lights;
    World* WorldPointer;
    std::unordered_map<std::string,our::Mesh*> meshes;
    std::unordered_map<std::string, our::ShaderProgram*> programs;
    std::unordered_map<std::string, Texture*> textures;




public:

    virtual void onEnter(our::Application* app);
    virtual void onExit(our::Application* app);
    virtual void onImmediateGui(ImGuiIO& io);
    virtual void loadResources(const nlohmann::json& json);
    virtual void attachPrograms(const nlohmann::json& json);
    virtual void onDraw(our::Application* app,double deltaTime);
    virtual void loadNode(const nlohmann::json& json,World* worldPointer,Entity* parent,our::Application* app,Sampler* s);
    // void resume();
    //void update();


};