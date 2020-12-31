//
// Created by Aya on 11/17/2020.
//

#include "World.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"

#include "Components/CameraComponent.h"
#include "Components/Material.h"
#include "Components/Light.h"
#include "Entity.h"
const int MAX_LIGHT_COUNT = 16;

//#include "Components\Camera.h"
Entity* World::createEntity(Entity* e) {
    //=new Entity();
    Entities.push_back(e);
    return e;
}
vector<Entity *>& World::getEntities() {
    return Entities;
}
// this function should be called in main game state 
/*void World::Rendering(){

    int Size=Entities.size();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<Size;i++)
    {
        if(Entities[i]->getComponent<MeshRenderer>()!=NULL)
        {
            Camera* c=getCameraEntity()->getComponent<Camera>();
            Transform* t=Entities[i]->getComponent<Transform>();
            CameraController* cc=getCameraEntity()->getComponent<CameraController>();
            //if(!c)return;
            //if(!cc)return;
            glm::mat4 vp=c->getProjectionMatrix()*cc->getCameraViewMatrix();
            glm::mat4 matrix1=vp*t->parents_mat(); //*view
            MeshRenderer* mesh=Entities[i]->getComponent<MeshRenderer>();
            our::Mesh* m=mesh->getPointerToMesh();
            our::ShaderProgram* p=mesh->getMaterial()->getPointerToProgram();
            Texture* tex=mesh->getMaterial()->getPointerToTexture();
            Sampler* sam=mesh->getMaterial()->getPointerToSampler();
            if(tex)tex->TextureBind();
            if(sam)sam->SamplerBind(p);
            std::any tint=mesh->getMaterial()->getUniform("tint");

            glm::vec4* Tint = std::any_cast<glm::vec4>(&tint);
            //if(!p)return;
            //if(!m) return;
            //if()
           // if(*p) return;
           // std::cout<<matrix1[0][0]<<" "<<matrix1[0][1]<<" "<<matrix1[0][2]<<" "<<matrix1[0][3]<<std::endl;
           // std::cout<<matrix1[0][0]<<" "<<matrix1[0][1]<<" "<<matrix1[0][2]<<" "<<matrix1[0][3]<<std::endl;
           if(Tint)cout <<(*Tint)[0]<<endl;
           glUseProgram(*p);
           p->set("transform", matrix1);
           p->set("tint", *Tint);
           /////call Entities[i]->getComponent<Texture>()->TextureBind() ////treat texture as comp??????
           ////call SamplerBind()
           m->draw();

        }
    }
}*/
GLenum blend_equation = GL_FUNC_ADD;
GLenum blend_source_function = GL_SRC_ALPHA, blend_destination_function = GL_ONE_MINUS_SRC_ALPHA;
glm::vec4 blend_constant_color = {1.0f,1.0f,1.0f,1.0f};
void World::RenderingSystem(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clearing the depth buffer is important now as we are drawing to it each frame.
   vector<LightComponent*> lights;
    /*glBlendEquation(blend_equation);
    glBlendFunc(blend_source_function, blend_destination_function);
    glBlendColor(blend_constant_color.r, blend_constant_color.g, blend_constant_color.b, blend_constant_color.a);*/
//    Some code to get the rendering camera entity.
    Entity* temp=getCameraEntity();
    Camera* c=temp->getComponent<Camera>();
    Transform* cameraTransform=temp->getComponent<Transform>();
    CameraController* cc=getCameraEntity()->getComponent<CameraController>();
    glm::mat4 vp=c->getProjectionMatrix()*c->getViewMatrix();
//            Collect all the lights

//    Let M be an empty container containing mesh renderers and their distance from the camera.
    std::unordered_multimap<std::shared_ptr<MeshRendererTransform>,long long> MTransparent;
    std::unordered_multimap<std::shared_ptr<MeshRendererTransform>,long long> MOpaque;
   // cout<<"start1"<<endl;

    for(auto & Entitie : Entities) {
        if(Entitie->getComponent<LightComponent>() != nullptr ) lights.push_back(Entitie->getComponent<LightComponent>());
        if (Entitie->getComponent<MeshRenderer>() != nullptr ) {
            Transform* t=Entitie->getComponent<Transform>();
            glm::mat4 matrix1=t->parents_mat();
            MeshRendererTransform* tempPair=new MeshRendererTransform();
            //cout<<"start3"<<endl;
            auto* tempPtr=Entitie->getComponent<MeshRenderer>();
            //cout<<"start4"<<endl;
            tempPair->MR=tempPtr;
            tempPair->matrix=matrix1;
            //cout<<"start5"<<endl;
            if(tempPtr->getMaterial()->getPointerToRenderState()->getTransparency())
                    MTransparent.insert(pair<std::shared_ptr<MeshRendererTransform>,long long>(tempPair,distance(cameraTransform,Entitie->getComponent<Transform>())));
                else
                    MOpaque.insert(pair<std::shared_ptr<MeshRendererTransform>,long long>(tempPair,distance(cameraTransform,Entitie->getComponent<Transform>())));

        }
    }
    cout<<"start2"<<endl;

    vector<pair<std::shared_ptr<MeshRendererTransform>,long long>> tmp;
    for (auto& i : MTransparent)
        tmp.push_back(i);
    // sort with descending order.
    sort(tmp.begin(), tmp.end(),
         [&](pair<std::shared_ptr<MeshRendererTransform>,long long>& a, pair<std::shared_ptr<MeshRendererTransform>,long long>& b) { return a.second > b.second; });
    cout<<"start3"<<endl;
    //    Loop on all M:
//    Setup the Material:
//    Use the shader program done
//    Send transform and camera variables to shader uniforms done
//    Send material variables to shader uniforms done
//    Send lights to shader uniforms


    for (auto& i : MOpaque)
    {

        //    Draw the entity using its attached mesh renderer component
        cout<<"start7"<<endl;
        our::Mesh* m=i.first->MR->getPointerToMesh();
        cout<<"start4"<<endl;
        our::ShaderProgram* p=i.first->MR->getMaterial()->getPointerToProgram();
        //Texture* tex=i.first->MR->getMaterial()->getPointerToTexture();
        Sampler* sam=i.first->MR->getMaterial()->getPointerToSampler();
        cout<<"start5"<<endl;
        //if(tex)tex->TextureBind();
        if(sam){
            cout<<"dkfjdksf"<<endl;
            for(GLuint unit = 0; unit < 5; ++unit)  sam->SamplerBind(p,unit);
        }
        std::any tint=i.first->MR->getMaterial()->getUniform("tint");
        glm::vec4* Tint = std::any_cast<glm::vec4>(&tint);
        std::any albedo_tint=i.first->MR->getMaterial()->getUniform("albedo_tint");
        glm::vec3* aTint = std::any_cast<glm::vec3>(&albedo_tint);
        std::any specular_tint=i.first->MR->getMaterial()->getUniform("specular_tint");
        glm::vec3* sTint = std::any_cast<glm::vec3>(&specular_tint);
        std::any roughness_range=i.first->MR->getMaterial()->getUniform("roughness_range");
        glm::vec2* rRange = std::any_cast<glm::vec2>(&roughness_range);
        std::any emissive_tint=i.first->MR->getMaterial()->getUniform("emissive_tint");
        glm::vec3* eTint = std::any_cast<glm::vec3>(&emissive_tint);
        std::any alpha=i.first->MR->getMaterial()->getUniform("alpha");
        float* Alpha = std::any_cast<float>(&alpha);
        cout<<"start9"<<endl;
        if(Tint)cout <<(*Tint)[0]<<endl;
        int light_index=0;

        glUseProgram(*p);
        p->set("alpha",*Alpha);
        p->set("camera_position", cc->getEye());
        p->set("view_projection", vp);
        p->set("sky_light.top_color", glm::vec3(0.0f));
        p->set("sky_light.middle_color", glm::vec3(0.0f));
        p->set("sky_light.bottom_color", glm::vec3(0.0f));
        cout<<"start11"<<endl;
        for(const auto& light : lights) {
            if(!(light->light.enabled)) continue;
            std::string prefix = "lights[" + std::to_string(light_index) + "].";
            light->lightSelect(p,prefix);
            light_index++;
            if(light_index >= MAX_LIGHT_COUNT) break;
        }
        cout<<"start10"<<endl;
        // cout<<light_index<<endl;
        p->set("light_count", light_index);

        p->set("object_to_world", i.first->matrix);
        p->set("object_to_world_inv_transpose", glm::inverse(i.first->matrix), true);
        cout<<"start13"<<endl;
        if(!aTint)cout<<"NOT"<<endl;
        p->set("material.albedo_tint", *aTint);
        p->set("material.specular_tint", *sTint);
        p->set("material.roughness_range", *rRange);
        p->set("material.emissive_tint", *eTint);
        cout<<"start12"<<endl;
        //cout<<(*eTint)[0]<<endl;
        Texture* albedoMap=i.first->MR->getMaterial()->getPointerToAlbedoMap();
        glActiveTexture(GL_TEXTURE0);
        albedoMap->TextureBind();
        p->set("material.albedo_map", 0);

        Texture* specularMap=i.first->MR->getMaterial()->getPointerToSpecularMap();
        glActiveTexture(GL_TEXTURE1);
        specularMap->TextureBind();
        p->set("material.specular_map", 1);


        Texture* ampientOcuulsionMap=i.first->MR->getMaterial()->getPointerToAmbientOcuulsionMap();
        glActiveTexture(GL_TEXTURE2);
        ampientOcuulsionMap->TextureBind();
        p->set("material.ambient_occlusion_map", 2);


        Texture* roughnessMap=i.first->MR->getMaterial()->getPointerToRoughnessMap();
        glActiveTexture(GL_TEXTURE3);
        roughnessMap->TextureBind();
        p->set("material.roughness_map", 3);

        Texture* emissiveMap=i.first->MR->getMaterial()->getPointerToEmissiveMap();
        glActiveTexture(GL_TEXTURE4);
        emissiveMap->TextureBind();
        p->set("material.emissive_map", 4);
        if(i.first->MR->getMaterial()->getPointerToEmissiveMap())cout<<"jkasjd"<<endl;


        //    Use the render state to set openGL state
        auto rs=i.first->MR->getMaterial()->getPointerToRenderState();
        rs->Blending();
        rs->Culling();
        rs->DepthTesting();
        m->draw();
       // cout<<"dsds,d;sld;sld;"<<endl;
    }
    for (auto& i : tmp){

        //    Draw the entity using its attached mesh renderer component
        our::Mesh* m=i.first->MR->getPointerToMesh();
        our::ShaderProgram* p=i.first->MR->getMaterial()->getPointerToProgram();
        //Texture* tex=i.first->MR->getMaterial()->getPointerToTexture();
        Sampler* sam=i.first->MR->getMaterial()->getPointerToSampler();
        //if(tex)tex->TextureBind();
        if(sam){
            cout<<"dkfjdksf"<<endl;
            for(GLuint unit = 0; unit < 5; ++unit) sam->SamplerBind(p,unit);
        }
        std::any tint=i.first->MR->getMaterial()->getUniform("tint");
        glm::vec4* Tint = std::any_cast<glm::vec4>(&tint);
        std::any albedo_tint=i.first->MR->getMaterial()->getUniform("albedo_tint");
        glm::vec3* aTint = std::any_cast<glm::vec3>(&albedo_tint);
        std::any specular_tint=i.first->MR->getMaterial()->getUniform("specular_tint");
        glm::vec3* sTint = std::any_cast<glm::vec3>(&specular_tint);
        std::any roughness_range=i.first->MR->getMaterial()->getUniform("roughness_range");
        glm::vec2* rRange = std::any_cast<glm::vec2>(&roughness_range);
        std::any emissive_tint=i.first->MR->getMaterial()->getUniform("emissive_tint");
        glm::vec3* eTint = std::any_cast<glm::vec3>(&emissive_tint);
        std::any alpha=i.first->MR->getMaterial()->getUniform("alpha");
        float* Alpha = std::any_cast<float>(&alpha);
        if(Tint)cout <<(*Tint)[0]<<endl;
        int light_index=0;

        glUseProgram(*p);
        p->set("alpha",*Alpha);
        p->set("camera_position", cc->getEye());
        p->set("view_projection", vp);
        p->set("sky_light.top_color", glm::vec3(0.0f));
        p->set("sky_light.middle_color", glm::vec3(0.0f));
        p->set("sky_light.bottom_color", glm::vec3(0.0f));
        for(const auto& light : lights) {
            if(!(light->light.enabled)) continue;
            std::string prefix = "lights[" + std::to_string(light_index) + "].";
            light->lightSelect(p,prefix);
            light_index++;
            if(light_index >= MAX_LIGHT_COUNT) break;
        }
        p->set("light_count", light_index);
        //p->set("transform", i.first->matrix);
        //p->set("tint", *Tint);
        p->set("object_to_world", i.first->matrix);
        p->set("object_to_world_inv_transpose", glm::inverse(i.first->matrix), true);
         p->set("material.albedo_tint", *aTint);
         p->set("material.specular_tint", *sTint);
         p->set("material.roughness_range", *rRange);
         p->set("material.emissive_tint", *eTint);
        Texture* albedoMap=i.first->MR->getMaterial()->getPointerToAlbedoMap();
        glActiveTexture(GL_TEXTURE0);
        albedoMap->TextureBind();
        p->set("material.albedo_map", 0);

        Texture* specularMap=i.first->MR->getMaterial()->getPointerToSpecularMap();
        glActiveTexture(GL_TEXTURE1);
        specularMap->TextureBind();
        p->set("material.specular_map", 1);


        Texture* ampientOcuulsionMap=i.first->MR->getMaterial()->getPointerToAmbientOcuulsionMap();
        glActiveTexture(GL_TEXTURE2);
        ampientOcuulsionMap->TextureBind();
        p->set("material.ambient_occlusion_map", 2);

        Texture* roughnessMap=i.first->MR->getMaterial()->getPointerToRoughnessMap();
        glActiveTexture(GL_TEXTURE3);
        roughnessMap->TextureBind();
        p->set("material.roughness_map", 3);

        Texture* emissiveMap=i.first->MR->getMaterial()->getPointerToEmissiveMap();
        glActiveTexture(GL_TEXTURE4);
        emissiveMap->TextureBind();
        p->set("material.emissive_map", 4);


        //    Use the render state to set openGL state
        auto rs=i.first->MR->getMaterial()->getPointerToRenderState();
        rs->Blending();
        rs->Culling();
        rs->DepthTesting();
        m->draw();
       // cout<<"dsds,d;sld;sld;"<<endl;
    }
   // cout<<"end"<<endl;


}

//won't be used;
glm::mat4 World::getCameraEntityTransform(){
    glm::mat4 mat=glm::mat4(1.0);
    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities[i]->getComponent<Camera>()!=NULL)
        {
            Transform* t=Entities[i]->getComponent<Transform>();
            return t->getMatrix();

        }
    }
    return mat;
}
 Entity* World::getCameraEntity(){

    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities.at(i)->getComponent<Camera>()!=NULL)
        {
            return Entities.at(i);
        }
    }
    return NULL;
}

Entity* World::getLightEntity(){

    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities.at(i)->getComponent<LightComponent>()!=NULL)
        {
            return Entities.at(i);
        }
    }
    return NULL;
}
World::~World() {

}