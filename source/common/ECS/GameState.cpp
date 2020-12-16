
// Created by m.yasser on 11/26/2020.
//#include <./application.hpp>
#include <fstream>

#include "GameState.h"
#include "Components/CameraComponent.h"
#include "./shader.hpp"
#include <mesh/mesh-utils.hpp>
#include <mesh/common-vertex-types.hpp>
#include <mesh/common-vertex-attributes.hpp>
#include"Components/Camera.h"
#include"Entity.h"
namespace glm {
    template<length_t L, typename T, qualifier Q>
    void from_json(const nlohmann::json& j, vec<L, T, Q>& v){
        for(length_t index = 0; index < L; ++index)
            v[index] = j[index].get<T>();
    }
}
/*void from_json(const nlohmann::json& j, Material& m){
    m.diffuse = j.value<glm::vec3>("diffuse", {0.0f, 0.0f, 0.0f});
    m.specular = j.value<glm::vec3>("specular", {0.0f, 0.0f, 0.0f});
    m.ambient = j.value<glm::vec3>("ambient", {0.0f, 0.0f, 0.0f});
    m.shininess = j.value<float>("shininess", 1.0f);
}
namespace our {
    void from_json(const nlohmann::json &j, our::Mesh &m) {
        m.diffuse = j.value<glm::vec3>("diffuse", {0.0f, 0.0f, 0.0f});
        m.specular = j.value<glm::vec3>("specular", {0.0f, 0.0f, 0.0f});
        m.ambient = j.value<glm::vec3>("ambient", {0.0f, 0.0f, 0.0f});
        m.shininess = j.value<float>("shininess", 1.0f);
    }
}*/
void GameState::onEnter(our::Application* app){
    //our::Application* App;
    //App=app;
//create our world
///when reserialization is completed
    WorldPointer=new World();

 // create a cam entity from world
    std::ifstream file_in("assets/data/scene.json");
    nlohmann::json json;
    file_in >> json;
    file_in.close();
    attachPrograms(json);
    loadResources(json);
    loadNode(json,WorldPointer,nullptr);

    int width, height;

    glfwGetFramebufferSize(app->getWindow(), &width, &height);
    Entity* CamEntity=new Entity();
    WorldPointer->createEntity(CamEntity);
    Transform* TransformCamera=new Transform({0,0,4},{0, 0, 0},{width, height, 0});
    Camera* CameraPointer=new Camera();


    CameraPointer->setupPerspective(glm::pi<float>()/2, static_cast<float>(width)/height, 0.1f, 100.0f);

    CameraController* CamControllerPointer=new CameraController(app,CameraPointer,TransformCamera);
    //CamControllerPointer->setTransform(TransformCamera);
    CamControllerPointer->setFieldOfViewSensitivity(0.05f );

    CamEntity->addComponent(TransformCamera);
    CamEntity->addComponent(CameraPointer);
    CamEntity->addComponent(CamControllerPointer);



/////////////////////////////////

   /* Entity* Object1=new Entity();
    WorldPointer->createEntity(Object1);
    Transform* TransformObject1=new Transform({0,0,0},{0,0,0},{1,1,0});

    our::ShaderProgram* program=new our::ShaderProgram ();
    //our::ShaderProgram* program=&programm;
    //our::Mesh quadd;
    our::Mesh* quad=new our::Mesh();

    program->create();
    program->attach("assets/shaders/ex11_transformation/transform.vert", GL_VERTEX_SHADER);
    program->attach("assets/shaders/ex11_transformation/tint.frag", GL_FRAGMENT_SHADER);
    program->link();

    // Create a mesh quad with colors passing the elements
    quad->create({our::setup_buffer_accessors<our::ColoredVertex>});
    quad->setVertexData<our::ColoredVertex>(0, {
            {{-0.5, -0.5, 0},{255,   0,   0, 255}},
            {{ 0.5, -0.5, 0},{  0, 255,   0, 255}},
            {{ 0.5,  0.5, 0},{  0,   0, 255, 255}},
            {{-0.5,  0.5, 0},{255, 255,   0, 255}}
    },GL_STATIC_DRAW);
    quad->setElementData<GLuint>({
                                         0, 1, 2,
                                         2, 3, 0
                                 },GL_STATIC_DRAW);
    Material* m1=new Material(program);
    MeshRenderer* MeshPointer=new MeshRenderer(quad,m1);

    Object1->addComponent(TransformObject1);
    Object1->addComponent(MeshPointer);

    ////////////////////////////////////////////////////////
    Entity* Object2=new Entity();
    WorldPointer->createEntity(Object2);

    Transform* TransformObject2=new Transform({-3,0,0},{0,0,0},{1,1,1});

    our::ShaderProgram* program1=new our::ShaderProgram();
    //our::ShaderProgram* program1=&program11;
    our::Mesh* PointerToquad1=new our::Mesh();
    //our::Mesh* PointerToquad1=&quad1;

    program1->create();
    program1->attach("assets/shaders/ex06_multiple_attributes/multiple_attributes.vert", GL_VERTEX_SHADER);
    program1->attach("assets/shaders/ex04_varyings/varying_color.frag", GL_FRAGMENT_SHADER);
    program1->link();
    Material* m2=new Material(program1);
    our::mesh_utils::loadOBJ(*PointerToquad1, "assets/models/Suzanne/Suzanne.obj");

    MeshRenderer* MeshPointer1=new MeshRenderer(PointerToquad1,m2);

    Object2->addComponent(TransformObject2);
    Object2->addComponent(MeshPointer1);*/
////////////////////////////////////////////////////////////////

// from the entitiy , get the camera controller component (generic fn)
//PointerToCamController = camera controller component


}
void GameState::onImmediateGui(ImGuiIO& io){



}

void GameState::onDraw(our::Application* app,double deltaTime){
    our::Application* App;
    App=app;

WorldPointer->getCameraEntity()->getComponent<CameraController>()->update(deltaTime);
WorldPointer->Rendering();

}

void GameState::onExit(our::Application* app) {
    //our::Application* App;
    //App=app;


    vector<Entity*> EntitiesToDelete=WorldPointer->getEntities();
    for(int i=0;i<EntitiesToDelete.size();i++){
        vector<Component*> componentsToDelete=EntitiesToDelete[i]->getComponents();
        for(int j=0;j<componentsToDelete.size();j++){
            MeshRenderer* t = nullptr;
            if ((t = dynamic_cast<MeshRenderer*>(componentsToDelete[j])) != nullptr){

                our::ShaderProgram* p=t->getMaterial()->getPointerToProgram();
                p->destroy();
                our::Mesh* m=t->getPointerToMesh();
                m->destroy();
            };
            delete componentsToDelete[j];
        }
        delete EntitiesToDelete[i];
    }
    delete WorldPointer;


}
void GameState::loadNode(const nlohmann::json& json,World* worldPointer,Entity* parent){
   // auto node = std::make_shared<Transform>(
            Entity* e=new Entity();
            worldPointer->createEntity(e);
            //ha7tag copy constructor
            glm::vec3 translation= json.value<glm::vec3>("translation", {0, 0, 0});
            glm::vec3 rotation= json.value<glm::vec3>("rotation", {0, 0, 0});
            glm::vec3 scale=json.value<glm::vec3>("scale", {1, 1, 1});
            std::cout<<translation.x<<","<<translation.y<<","<<translation.z<<std::endl;
            Transform* t=new Transform(translation,rotation,scale,parent);
            e->addComponent(t);
    //);
    if(json.contains("mesh")&&json.contains("program")){
        if(auto mesh_it = meshes.find(json["mesh"].get<std::string>()); mesh_it != meshes.end()) {
            if(auto prog_it = programs.find(json["program"].get<std::string>()); prog_it != programs.end()) {
                Material *mat=new Material(prog_it->second);
                MeshRenderer* meshRenderer=new MeshRenderer(mesh_it->second,mat);
                e->addComponent(meshRenderer);
            }
        }
    }

    if(json.contains("children")){
        for(auto& [name, child]: json["children"].items()){
            loadNode(child,worldPointer,e);
        }
    }
    //return node;
}
void GameState::loadResources(const nlohmann::json& json){
    if(json.contains("resources")){

        for (auto& [key, val] : json["resources"]["meshes"].items())
        {
            our::Mesh* mp=new our::Mesh();
            meshes[key] =mp;
            our::mesh_utils::loadOBJ(*(meshes[key]),json["resources"]["meshes"].value<std::string>(key, "").c_str());
        }
    }


}
void GameState::attachPrograms(const nlohmann::json& json){
    if(json.contains("resources")){

        for(auto& [name, it]: json["resources"]["programs"].items()){
            our::ShaderProgram* pp= new our::ShaderProgram();
            std::cout<<"xxxxxxxxxxxxxxxxx"<<std::endl;
            std::cout<<name<<std::endl;
            if(it.contains("vert")){
                std::cout<<it.value<std::string>("vert", "")<<std::endl;
                pp->create();
                pp->attach(it.value<std::string>("vert", ""), GL_VERTEX_SHADER);

                pp->attach(it.value<std::string>("frag", ""), GL_FRAGMENT_SHADER);
                pp->link();
            }
            programs[name]=pp;

        }

    }


}

//    void resume(){}
//    void update(){}

