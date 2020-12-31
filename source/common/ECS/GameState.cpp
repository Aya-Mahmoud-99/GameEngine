
// Created by m.yasser on 11/26/2020.
//#include <./application.hpp>
#include "utils.hpp"
#include <fstream>
#include "GameState.h"
#include "Components/CameraComponent.h"
#include "./shader.hpp"
#include <mesh/mesh-utils.hpp>
#include <mesh/common-vertex-types.hpp>
#include <mesh/common-vertex-attributes.hpp>
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
void from_json(const nlohmann::json& j, Light& l){
    std::string type_name = j.value("type", "point");
    std::transform(type_name.begin(), type_name.end(), type_name.begin(), [](char c){ return std::tolower(c); });
    if(type_name == "directional") l.type = LightType::DIRECTIONAL;
    else if(type_name == "spot") l.type = LightType::SPOT;
    else l.type = LightType::POINT;
    l.color = j.value<glm::vec3>("color", {1,1,1});
 //   l.direction = j.value<glm::vec3>("direction", {0, -1, 0});
//    l.position = j.value<glm::vec3>("position", {0,0,0});
    l.enabled = j.value("enabled", true);
    if(auto it = j.find("attenuation"); it != j.end()){
        auto& a = it.value();
        l.attenuation.constant = a.value("constant", 0.0f);
        l.attenuation.linear = a.value("linear", 0.0f);
        l.attenuation.quadratic = a.value("quadratic", 1.0f);
    } else {
        l.attenuation = {0.0f, 0.0f, 1.0f};
    }
    if(auto it = j.find("spot_angle"); it != j.end()){
        auto& a = it.value();
        l.spot_angle.inner = a.value("inner", glm::quarter_pi<float>());
        l.spot_angle.outer = a.value("outer", glm::half_pi<float>());
    } else {
        l.spot_angle = {glm::quarter_pi<float>(), glm::half_pi<float>()};
    }
}
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
    Sampler* s=new Sampler();
    loadNode(json,WorldPointer,nullptr,app,s); ///to be edited to load textures of each Entity///to be edited to load Light component
    /////in LoadNode call Texture() for each Entity
    ////call Sampler() once (one Sampler for all Entities)
/* int width, height;

    glfwGetFramebufferSize(app->getWindow(), &width, &height);
    Entity* CamEntity=new Entity();
    WorldPointer->createEntity(CamEntity);
    Transform* TransformCamera=new Transform({0,0,4},{0, 0, 0},{1, 1, 0});
    Camera* CameraPointer=new Camera();
    std::cout<<glm::pi<float>()/2<<std::endl;
    std::cout<<static_cast<float>(width)/height<<std::endl;


    CameraPointer->setupPerspective(glm::pi<float>()/2, static_cast<float>(width)/height, 0.1f, 100.0f);

    CameraController* CamControllerPointer=new CameraController(app,CameraPointer,TransformCamera);
    //CamControllerPointer->setTransform(TransformCamera);
    CamControllerPointer->setFieldOfViewSensitivity(0.05f );

    CamEntity->addComponent(TransformCamera);
    CamEntity->addComponent(CameraPointer);
    CamEntity->addComponent(CamControllerPointer);

*/

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
/////////////////////////////////////////to be added lightcomp update/////////////////////////////////////////////////
//int light_index = 0;
//const int MAX_LIGHT_COUNT = 16;
//WorldPointer->getLightEntity()->getComponent<LightComponent>()->lightSelect(light_index,MAX_LIGHT_COUNT,program);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//cout<<"xxxxxxxx"<<endl;
WorldPointer->getCameraEntity()->getComponent<CameraController>()->update(deltaTime);
  //  cout<<"xxxxxxxx"<<endl;
//WorldPointer->Rendering();///to be edited to add TextureBind and SamplerBind
    WorldPointer->RenderingSystem();
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
void GameState::loadNode(const nlohmann::json& json,World* worldPointer,Entity* parent,our::Application* app,Sampler* s){
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
    if(json.contains("camera")){
        int width, height;
        glfwGetFramebufferSize(app->getWindow(), &width, &height);
        Camera* CameraPointer=new Camera();
        if(json["camera"].value<std::string>("type","prespective")=="prespective")CameraPointer->setupPerspective(json["camera"].value<float>("field_of_view",glm::pi<float>()/2 ), json["camera"].value<float>("aspect_ratio",static_cast<float>(width)/height ), json["camera"].value<float>("near",0.1f ), json["camera"].value<float>("far",100.0f));
        if(json["camera"].value<std::string>("type","prespective")=="orthographic")CameraPointer->setupOrthographic(json["camera"].value<float>("orthographic_height",glm::pi<float>()/2 ), json["camera"].value<float>("aspect_ratio",static_cast<float>(width)/height ), json["camera"].value<float>("near",0.1f ), json["camera"].value<float>("far",100.0f));
        if(json["camera"].value<std::string>("camera_controller","true")=="true") {
            CameraController *CamControllerPointer = new CameraController(app, CameraPointer, t);
            e->addComponent(CamControllerPointer);
        }e->addComponent(CameraPointer);
    }
    if(json.contains("light")){
        Light l;
        l=json.value("light",l );
        LightComponent* L=new LightComponent(l,t);
        e->addComponent(L);
    }
    if(json.contains("mesh")&&json.contains("program")){
        if(auto mesh_it = meshes.find(json["mesh"].get<std::string>()); mesh_it != meshes.end()) {
            if(auto prog_it = programs.find(json["program"].get<std::string>()); prog_it != programs.end()) {
                Material *mat=new Material(prog_it->second);
               /* Texture* albedo_map;
                Texture* specular_map;
                Texture* ambient_occlusion_map;
                Texture* roughness_map;
                Texture* emissive_map;*/
                mat->setPointerToSampler(s);
                if(json.contains("albedo_map")){/////////////////////////////////////////////////////////////////////////////
                    if(auto tex_it = textures.find(json["albedo_map"].get<std::string>()); tex_it != textures.end()) {
                        mat->setPointerToAlbedoMap(tex_it->second);
                        cout<<"aya "<<tex_it->first<<endl;
                    }
                }
                if(json.contains("specular_map")){/////////////////////////////////////////////////////////////////////////////
                    if(auto tex_it = textures.find(json["specular_map"].get<std::string>()); tex_it != textures.end()) {
                        mat->setPointerToSpecularMap(tex_it->second);
                        cout<<"aya "<<tex_it->first<<endl;
                       // mat->setPointerToSampler(s);
                    }
                }
                if(json.contains("ambient_occlusion_map")){/////////////////////////////////////////////////////////////////////////////
                    if(auto tex_it = textures.find(json["ambient_occlusion_map"].get<std::string>()); tex_it != textures.end()) {
                        mat->setPointerToAmbientOcuulsionMap(tex_it->second);
                        cout<<"aya "<<tex_it->first<<endl;
                       // mat->setPointerToSampler(s);
                    }
                }
                if(json.contains("roughness_map")){/////////////////////////////////////////////////////////////////////////////
                    if(auto tex_it = textures.find(json["roughness_map"].get<std::string>()); tex_it != textures.end()) {
                        mat->setPointerToRoughnessMap(tex_it->second);
                        cout<<"aya "<<tex_it->first<<endl;
                        //mat->setPointerToSampler(s);
                    }
                }
                if(json.contains("emissive_map")){/////////////////////////////////////////////////////////////////////////////
                    if(auto tex_it = textures.find(json["emissive_map"].get<std::string>()); tex_it != textures.end()) {
                        mat->setPointerToEmissiveMap(tex_it->second);
                        cout<<"aya "<<tex_it->first<<endl;
                       // mat->setPointerToSampler(s);
                    }
                }
                if(json.contains("uniforms")){
                    cout<<"dsdsdsd"<<endl;
                    for (auto& [key, val] : json["uniforms"].items())
                    {
                        std::string type=json["uniforms"][key].value<std::string>("type","");
                      if(type=="vec4")mat->addUniform(key,json["uniforms"][key].value<glm::vec4>("value", {1,0,0,1}));
                        if(type=="vec2")mat->addUniform(key,json["uniforms"][key].value<glm::vec2>("value", {1,0}));
                        if(type=="vec3")mat->addUniform(key,json["uniforms"][key].value<glm::vec3>("value", {1,1,1}));
                        if(type=="float")mat->addUniform(key,json["uniforms"][key].value<float>("value",1.0f));


                        cout<<key<<" "<<val<<endl;
                    }
                }

                if(json.contains("render_state")){
                 RenderState* r=new RenderState(
                        json["render_state"]["depth_enable"]==1?true:false,
                        enum_options::dpFunc[json["render_state"].value<std::string>("dpfunc","GL_LEQUAL")],
                        json["render_state"]["cull_enable"]==1?true:false,
                        enum_options::cullface[json["render_state"].value<std::string>("cullface","GL_BACK")],
                        enum_options::frontwinding[json["render_state"].value<std::string>("frontwinding","GL_CCW")],
                        json["render_state"]["blend_enable"]==1?true:false,
                        enum_options::blendFun[json["render_state"].value<std::string>("blendFun","GL_FUNC_ADD")],
                        enum_options::source[json["render_state"].value<std::string>("source","GL_SRC_ALPHA")],
                        enum_options::dest[json["render_state"].value<std::string>("dest","GL_ONE_MINUS_SRC_ALPHA")],
                        json["render_state"]["transperent"]==1?true:false
                                );
                 cout<<json["render_state"].value<std::string>("dpfunc","mama")<<endl;
                 mat->setPointerToRenderState(r);
                }
                MeshRenderer* meshRenderer=new MeshRenderer(mesh_it->second,mat);
                e->addComponent(meshRenderer);
            }
        }
    }
 /*   if(json.contains("texture")){/////////////////////////////////////////////////////////////////////////////
        e->texture = json["texture"].get<std::string>();
    }*/

    if(json.contains("children")){
        for(auto& [name, child]: json["children"].items()){
            loadNode(child,worldPointer,e,app,s);
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
        if(json["resources"].contains("textures")) {
            for (auto&[key, val] : json["resources"]["textures"].items()) {
                Texture *tex = new Texture(json["resources"]["textures"].value<std::string>(key, "").c_str());
                cout<<"texture"<<" "<<json["resources"]["textures"].value<std::string>(key, "").c_str()<<endl;
                textures[key] = tex;
            }
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
                std::cout<<"yyyyyyyyyyyyyyyy"<<std::endl;

                pp->attach(it.value<std::string>("frag", ""), GL_FRAGMENT_SHADER);
                std::cout<<"yyyyyyyyyyyyyyyy"<<std::endl;

                pp->link();
                std::cout<<"yyyyyyyyyyyyyyyy"<<std::endl;

            }
            programs[name]=pp;

        }

    }


}

//    void resume(){}
//    void update(){}

