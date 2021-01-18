//
// Created by Aya on 11/17/2020.
//

#include "World.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"
//#include "Egg.h"

#include "Components/CameraComponent.h"
#include "Components/Material.h"
#include "Components/Light.h"
//#include "Entity.h"
const int MAX_LIGHT_COUNT = 16;

//#include "Components\Camera.h"
World::World(){
    smashedEgg=new Sound("assets/tracks/Mirror Shattering-SoundBible.com-1752328245.mp3",false);
    chickenFlag=30;
}
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
    //vector<Bullet*> bulletsVector;
//    Let M be an empty container containing mesh renderers and their distance from the camera.
    std::vector<pair<std::shared_ptr<MeshRendererTransform>,double>> MTransparent;
    std::vector<pair<std::shared_ptr<MeshRendererTransform>,double>> MOpaque;
   // cout<<"start1"<<endl;

    for(auto & Entitie : Entities) {
        /*if(Entitie->getComponent<SpaceShipController>() != nullptr)
        {
            bulletsVector=Entitie->getComponent<SpaceShipController>()->getPointerToBulletsVector();
        }*/
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
            glm::vec3 distanceVector=(cameraTransform->getPosition())-(Entitie->getComponent<Transform>()->getPosition());
            double dist=sqrt(pow(distanceVector.x,2)+pow(distanceVector.y,2)+pow(distanceVector.z,2));
            if(tempPtr->getMaterial()->getPointerToRenderState()->getTransparency())
                    MTransparent.push_back(pair<std::shared_ptr<MeshRendererTransform>,double>(tempPair,dist));
                else
                    MOpaque.push_back(pair<std::shared_ptr<MeshRendererTransform>,double>(tempPair,dist));

        }
    }

    // sort with descending order.
    sort(MTransparent.begin(), MTransparent.end(),
         [&](pair<std::shared_ptr<MeshRendererTransform>,double>& a, pair<std::shared_ptr<MeshRendererTransform>, double>& b) { return a.second > b.second; });


    for (auto& i : MOpaque)
    {

        //    Draw the entity using its attached mesh renderer component
       // cout<<"start7"<<endl;
        our::Mesh* m=i.first->MR->getPointerToMesh();
       // cout<<"start4"<<endl;
        our::ShaderProgram* p=i.first->MR->getMaterial()->getPointerToProgram();
        //Texture* tex=i.first->MR->getMaterial()->getPointerToTexture();
        Sampler* sam=i.first->MR->getMaterial()->getPointerToSampler();
       // cout<<"start5"<<endl;
        //if(tex)tex->TextureBind();
        if(sam){
            //cout<<"dkfjdksf"<<endl;
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
        //cout<<"start99"<<endl;
        if(Tint)cout <<(*Tint)[0]<<endl;
        int light_index=0;

        glUseProgram(*p);
        //cout<<"start10"<<endl;
        p->set("alpha",*Alpha);
        //cout<<"start11"<<endl;
        p->set("camera_position", cc->getEye());
        //cout<<"start12"<<endl;
        p->set("view_projection", vp);
        //cout<<"start13"<<endl;
        p->set("sky_light.top_color", glm::vec3(0.0f));
        p->set("sky_light.middle_color", glm::vec3(0.0f));
        p->set("sky_light.bottom_color", glm::vec3(0.0f));
        //cout<<"start11"<<endl;
        for(const auto& light : lights) {
            if(!(light->light.enabled)) continue;
            std::string prefix = "lights[" + std::to_string(light_index) + "].";
            light->lightSelect(p,prefix);
            light_index++;
            if(light_index >= MAX_LIGHT_COUNT) break;
        }
       // cout<<"start10"<<endl;
        // cout<<light_index<<endl;
        p->set("light_count", light_index);

        p->set("object_to_world", i.first->matrix);
        p->set("object_to_world_inv_transpose", glm::inverse(i.first->matrix), true);
       // cout<<"start13"<<endl;
        if(!aTint)cout<<"NOT"<<endl;
        p->set("material.albedo_tint", *aTint);
        p->set("material.specular_tint", *sTint);
        p->set("material.roughness_range", *rRange);
        p->set("material.emissive_tint", *eTint);
       // cout<<"start12"<<endl;
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
       // if(i.first->MR->getMaterial()->getPointerToEmissiveMap())cout<<"jkasjd"<<endl;


        //    Use the render state to set openGL state
        auto rs=i.first->MR->getMaterial()->getPointerToRenderState();
        rs->Blending();
        rs->Culling();
        rs->DepthTesting();
        m->draw();
       // cout<<"dsds,d;sld;sld;"<<endl;
    }
    for (auto& i : MTransparent){

        //    Draw the entity using its attached mesh renderer component
        our::Mesh* m=i.first->MR->getPointerToMesh();
        our::ShaderProgram* p=i.first->MR->getMaterial()->getPointerToProgram();
        //Texture* tex=i.first->MR->getMaterial()->getPointerToTexture();
        Sampler* sam=i.first->MR->getMaterial()->getPointerToSampler();
        //if(tex)tex->TextureBind();
        if(sam){
         //   cout<<"dkfjdksf"<<endl;
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
Entity* World::getSpaceShipEntity(){

    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities.at(i)->getComponent<SpaceShipController>()!=NULL)
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
void World::getTagEntities(vector<Entity*>& entities,string tag){
    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities.at(i)&&Entities.at(i)->getEntityName()==tag)
        {
            //cout<<"makan 2el far5a 2le 2et7at"<<(Entities.at(i)->getComponent<Transform>()->getPosition())[1]<<endl;
            entities.push_back(Entities.at(i));
        }
    }
}
void World::generateEggs() {
    vector<Entity*> chickens;
    getTagEntities(chickens,"chicken");
    int size=chickens.size();
    std::cout<<"size"<<size<<endl;
    int rand1=std::rand()%(10);
    int rand2=std::rand()%(10);
    if(size!=0&&rand1<1&&rand2<2) {
       // std::srand(time(0));
        int randEgg = std::rand() % (size);
        Entity *genratorChicken = chickens.at(randEgg);
        Transform *chickTranform = genratorChicken->getComponent<Transform>();
      //  cout<<"heeeeeeeeeeeeeeeeeeeeeeeeeh"<<endl;
      //  cout<<"RANDDDDDEGGG"<<randEgg<<endl;
      //  cout<<"makan 2el far5a"<<(chickTranform->getPosition())[1]<<endl;
       // cout<<"makan 2el beida"<<(chickTranform->getPosition()+glm::vec3{0,-1,0})[1]<<endl;
      //  Egg *e = new Egg(chickTranform->getPosition()+glm::vec3{0,-1,0});
        Entity* e=new Entity();
        e->addComponent(EggRenderer);
        Transform* t=new Transform(chickTranform->getPosition()+glm::vec3{0,-1,0});
        e->addComponent(t);
        e->setEntityName("egg");
        Entities.push_back(e);
    }
}

void World::LoadEgg(){
    our::ShaderProgram *pp = new our::ShaderProgram();
    pp->create();
    pp->attach("assets/shaders/ex29_light/light_transform.vert", GL_VERTEX_SHADER);

    pp->attach("assets/shaders/ex32_textured_material/light_array.frag", GL_FRAGMENT_SHADER);

    pp->link();
    our::Mesh* mp=new our::Mesh();
    our::mesh_utils::loadOBJ(*mp,"assets/models/egg/egg.obj");
    Texture *tex = new Texture("assets/models/egg/Plastic010_1K_Color.jpg");
    //
    Material *mat=new Material(pp);
    mat->setPointerToEmissiveMap(tex);
    mat->setPointerToRoughnessMap(tex);
    mat->setPointerToAmbientOcuulsionMap(tex);
    mat->setPointerToSpecularMap(tex);
    mat->setPointerToAlbedoMap(tex);
    Sampler* s=new Sampler();
    mat->setPointerToSampler(s);
    mat->addUniform("alpha",1.0f);
    mat->addUniform("specular_tint",glm::vec3{1,1,1});
    mat->addUniform("emissive_tint",glm::vec3{1,1,1});
    mat->addUniform("albedo_tint",glm::vec3{1,1,1});
    mat->addUniform("roughness_range",glm::vec2{0,1});
    RenderState* r=new RenderState(
            true,
            GL_LEQUAL,
            false,
            GL_FRONT,
            GL_CCW,
            false,
            GL_FUNC_ADD,
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            false
    );
    mat->setPointerToRenderState(r);
    EggRenderer=new MeshRenderer(mp,mat);

}
void World::LoadHeart(){
    our::ShaderProgram *pp = new our::ShaderProgram();
    cout<<"1111111111111111111111"<<endl;
    pp->create();
    pp->attach("assets/shaders/ex29_light/light_transform.vert", GL_VERTEX_SHADER);

    pp->attach("assets/shaders/ex32_textured_material/light_array.frag", GL_FRAGMENT_SHADER);

    pp->link();
    cout<<"222222222222222222222222"<<endl;

    our::Mesh* mp=new our::Mesh();
    cout<<"999999999999999999999999"<<endl;
    our::mesh_utils::loadOBJ(*mp,"assets/models/heart/uploads_files_2036667_LP_heart_OBJ.obj");
    cout<<"7777777777777777777"<<endl;
    Texture *tex = new Texture("assets/models/heart/red.jpg");
    cout<<"888888888888888888888888"<<endl;
    Material *mat=new Material(pp);
    cout<<"3333333333333333333333333"<<endl;

    mat->setPointerToEmissiveMap(tex);
    mat->setPointerToRoughnessMap(tex);
    mat->setPointerToAmbientOcuulsionMap(tex);
    mat->setPointerToSpecularMap(tex);
    mat->setPointerToAlbedoMap(tex);
    cout<<"444444444444444444444444444"<<endl;

    Sampler* s=new Sampler();
    mat->setPointerToSampler(s);
    mat->addUniform("alpha",1.0f);
    mat->addUniform("specular_tint",glm::vec3{1,1,1});
    mat->addUniform("emissive_tint",glm::vec3{1,1,1});
    mat->addUniform("albedo_tint",glm::vec3{1,1,1});
    mat->addUniform("roughness_range",glm::vec2{0,1});
    cout<<"5555555555555555555555555555555555"<<endl;

    RenderState* r=new RenderState(
            true,
            GL_LEQUAL,
            false,
            GL_FRONT,
            GL_CCW,
            false,
            GL_FUNC_ADD,
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            false
    );
    mat->setPointerToRenderState(r);
    HeartRenderer=new MeshRenderer(mp,mat);
    cout<<"6666666666666666666666666666666666666"<<endl;

}
void World::LoadBrokenEgg(){
    our::ShaderProgram *pp = new our::ShaderProgram();
    cout<<"1111111111111111111111"<<endl;
    pp->create();
    pp->attach("assets/shaders/ex29_light/light_transform.vert", GL_VERTEX_SHADER);

    pp->attach("assets/shaders/ex32_textured_material/light_array.frag", GL_FRAGMENT_SHADER);

    pp->link();
    cout<<"222222222222222222222222"<<endl;

    our::Mesh* mp=new our::Mesh();
    cout<<"999999999999999999999999"<<endl;
    our::mesh_utils::loadOBJ(*mp,"assets/models/crackedegg/easter-egg.obj");
    cout<<"7777777777777777777"<<endl;
    Texture *tex = new Texture("assets/models/egg/Plastic010_1K_Color.jpg");
    cout<<"888888888888888888888888"<<endl;
    Material *mat=new Material(pp);
    cout<<"3333333333333333333333333"<<endl;

    mat->setPointerToEmissiveMap(tex);
    mat->setPointerToRoughnessMap(tex);
    mat->setPointerToAmbientOcuulsionMap(tex);
    mat->setPointerToSpecularMap(tex);
    mat->setPointerToAlbedoMap(tex);
    cout<<"444444444444444444444444444"<<endl;

    Sampler* s=new Sampler();
    mat->setPointerToSampler(s);
    mat->addUniform("alpha",1.0f);
    mat->addUniform("specular_tint",glm::vec3{1,1,1});
    mat->addUniform("emissive_tint",glm::vec3{1,1,1});
    mat->addUniform("albedo_tint",glm::vec3{1,1,1});
    mat->addUniform("roughness_range",glm::vec2{0,1});
    cout<<"5555555555555555555555555555555555"<<endl;

    RenderState* r=new RenderState(
            true,
            GL_LEQUAL,
            false,
            GL_FRONT,
            GL_CCW,
            false,
            GL_FUNC_ADD,
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            false
    );
    mat->setPointerToRenderState(r);
    BrokenEggRenderer=new MeshRenderer(mp,mat);
    cout<<"6666666666666666666666666666666666666"<<endl;

}
void World::moveEggs() {
    vector<Entity*> eggs;
    getTagEntities(eggs,"egg");
    int size=eggs.size();
    cout<<"eggs"<<size<<endl;
    for(int i=0;i<size;i++)
    {
            Transform* eTransfrom=eggs.at(i)->getComponent<Transform>();
            glm::vec3 positionNow=eTransfrom->getPosition();
            eTransfrom->setPosition(positionNow+glm::vec3{0,-0.1,0});
            bool collided=World::checkCollisionWithPlayer(eTransfrom->getPosition());
            eggs.at(i)->setCollided(collided);
            if(collided) {
                smashedEgg->stop();
                smashedEgg->play();
                cout<<"COLLISION DETECTED"<<endl;
            }

    }
}
void World::deleteEggsOnGround() {
   int Size = Entities.size();
    for (int i = 0; i < Size; i++) {
        if (Entities.at(i)->getEntityName() == "egg" &&
            (Entities.at(i)->getComponent<Transform>()->getPosition()[1] < -8 || Entities.at(i)->getCollided())) {
            if (Entities.at(i)->getComponent<Transform>()->getPosition()[1] < -8) {
                Entity *e = new Entity();
                e->addComponent(BrokenEggRenderer);
                Transform *t = new Transform(Entities.at(i)->getComponent<Transform>()->getPosition());
                e->addComponent(t);
                e->setEntityName("brokenegg");
                Entities.push_back(e);
                Size++;
            }
            Entity *egg = Entities.at(i);
            Entities.erase(Entities.begin() + i);
            i--;
            delete egg;
            Size--;
        }



        if (Entities.at(i)->getEntityName() == "heart" ) {
            Entity *heart = Entities.at(i);
            Entities.erase(Entities.begin() + i);
            i--;
            delete heart;
            Size--;
        }


        if (Entities.at(i)->getEntityName() == "brokenegg") {
            Entities.at(i)->setCounter(Entities.at(i)->getCounter() + 1);
            if (Entities.at(i)->getCounter() == 40) {
                Entity *egg = Entities.at(i);
                Entities.erase(Entities.begin() + i);
                i--;
                delete egg;
                Size--;
            }

        }
    }
}
bool World::checkCollisionWithPlayer(glm::vec3 eggPosition){
    vector<Entity*> players;
    getTagEntities(players,"player");
    Entity* player=players[0];
    Transform* playerTransfrom=player->getComponent<Transform>();
    glm::vec3 playerPosition=playerTransfrom->getPosition();
    bool collision=false;
    if(eggPosition[1]<=playerPosition[1]+1&&eggPosition[1]>=playerPosition[1]-1){
        if(eggPosition[0]<=playerPosition[0]+1&&eggPosition[0]>=playerPosition[0]-1){
            //cout<<"COLLISSION DETECTED"<<endl;
            player->getComponent<SpaceShipController>()->setLives(player->getComponent<SpaceShipController>()->getLives()-1);
            collision=true;
        }

    }
    for(int i=0;i<player->getComponent<SpaceShipController>()->getLives();i++){
        Entity* e=new Entity();
        e->addComponent(HeartRenderer);
        Transform* t=new Transform(glm::vec3{14+i*4,-10,0},glm::vec3{0,1.5,0},glm::vec3{0.03,0.03,0.03});
        e->addComponent(t);
        e->setEntityName("heart");
        Entities.push_back(e);
    }
    return collision;
};
void World::moveChickens(){
    vector<Entity*> chickens;
    getTagEntities(chickens,"chicken");
    int size=chickens.size();
    for(int i=0;i<size;i++){
        glm::vec3 chickenPosition=chickens.at(i)->getComponent<Transform>()->getPosition();
        if(chickenFlag<=60){
            chickenPosition=chickenPosition+glm::vec3 {0.01,0,0};
        }
        else {
            chickenPosition = chickenPosition + glm::vec3{-0.01, 0, 0};
        }
        chickens.at(i)->getComponent<Transform>()->setPosition(chickenPosition);
    }

    chickenFlag++;
    if(chickenFlag==120){
        chickenFlag=0;
    }
}
void World::setBulletRenderer(Texture*ts,our::Mesh*ms,our::ShaderProgram*p){

    our::ShaderProgram *pp = new our::ShaderProgram();
    pp->create();
    pp->attach("assets/shaders/ex29_light/light_transform.vert", GL_VERTEX_SHADER);
    pp->attach("assets/shaders/ex32_textured_material/light_array.frag", GL_FRAGMENT_SHADER);
    pp->link();
    our::Mesh* mp=new our::Mesh();
    our::mesh_utils::loadOBJ(*mp,"assets/models/bullet/556-rifle-bullet.obj");
    Texture *tex = new Texture("assets/models/bullet/Metal035_1K_Color.jpg");
    Material *mat=new Material(pp);
    mat->setPointerToEmissiveMap(tex);
    mat->setPointerToRoughnessMap(tex);
    mat->setPointerToAmbientOcuulsionMap(tex);
    mat->setPointerToSpecularMap(tex);
    mat->setPointerToAlbedoMap(tex);
    Sampler* s=new Sampler();
    mat->setPointerToSampler(s);
    mat->addUniform("alpha",1.0f);
    mat->addUniform("specular_tint",glm::vec3{1,1,1});
    mat->addUniform("emissive_tint",glm::vec3{1,1,1});
    mat->addUniform("albedo_tint",glm::vec3{1,1,1});
    mat->addUniform("roughness_range",glm::vec2{0,1});
    RenderState* r=new RenderState(
            true,
            GL_LEQUAL,
            false,
            GL_FRONT,
            GL_CCW,
            false,
            GL_FUNC_ADD,
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            false
    );
    mat->setPointerToRenderState(r);
    bulletRenderer=new MeshRenderer(mp,mat);
    

}

void World::setScoreRenderer(Texture*ts,our::Mesh*ms,our::ShaderProgram*p){

    our::ShaderProgram *pp = new our::ShaderProgram();
    pp->create();
    pp->attach("assets/shaders/ex29_light/light_transform.vert", GL_VERTEX_SHADER);
    pp->attach("assets/shaders/ex32_textured_material/light_array.frag", GL_FRAGMENT_SHADER);
    pp->link();
    our::Mesh* mp=new our::Mesh();
    our::mesh_utils::loadOBJ(*mp,"assets/models/background/uploads_files_648761_cube.obj");
    Texture *tex = new Texture("assets/Textures/colors.jpeg");
    Material *mat=new Material(pp);
    mat->setPointerToEmissiveMap(tex);
    mat->setPointerToRoughnessMap(tex);
    mat->setPointerToAmbientOcuulsionMap(tex);
    mat->setPointerToSpecularMap(tex);
    mat->setPointerToAlbedoMap(tex);
    Sampler* s=new Sampler();
    mat->setPointerToSampler(s);
    mat->addUniform("alpha",1.0f);
    mat->addUniform("specular_tint",glm::vec3{1,1,1});
    mat->addUniform("emissive_tint",glm::vec3{1,1,1});
    mat->addUniform("albedo_tint",glm::vec3{1,1,1});
    mat->addUniform("roughness_range",glm::vec2{0,1});
    RenderState* r=new RenderState(
            true,
            GL_LEQUAL,
            false,
            GL_FRONT,
            GL_CCW,
            false,
            GL_FUNC_ADD,
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            false
    );
    mat->setPointerToRenderState(r);
    scoreCube=new MeshRenderer(mp,mat);

}

MeshRenderer* World::getScoreRenderer(){
    return scoreCube;
}


void World::LoadGameOver(){
    our::ShaderProgram *pp = new our::ShaderProgram();
    cout<<"1111111111111111111111"<<endl;
    pp->create();
    pp->attach("assets/shaders/ex29_light/light_transform.vert", GL_VERTEX_SHADER);

    pp->attach("assets/shaders/ex32_textured_material/light_array.frag", GL_FRAGMENT_SHADER);

    pp->link();
    cout<<"222222222222222222222222"<<endl;

    our::Mesh* mp=new our::Mesh();
    cout<<"999999999999999999999999"<<endl;
    our::mesh_utils::loadOBJ(*mp,"assets/models/background/uploads_files_648761_cube.obj");
    cout<<"7777777777777777777"<<endl;
    Texture *tex = new Texture("assets/images/common/GameOver.jpg");
    cout<<"888888888888888888888888"<<endl;
    Material *mat=new Material(pp);
    cout<<"3333333333333333333333333"<<endl;

    mat->setPointerToEmissiveMap(tex);
    mat->setPointerToRoughnessMap(tex);
    mat->setPointerToAmbientOcuulsionMap(tex);
    mat->setPointerToSpecularMap(tex);
    mat->setPointerToAlbedoMap(tex);
    cout<<"444444444444444444444444444"<<endl;

    Sampler* s=new Sampler();
    mat->setPointerToSampler(s);
    mat->addUniform("alpha",1.0f);
    mat->addUniform("specular_tint",glm::vec3{1,1,1});
    mat->addUniform("emissive_tint",glm::vec3{1,1,1});
    mat->addUniform("albedo_tint",glm::vec3{1,1,1});
    mat->addUniform("roughness_range",glm::vec2{0,1});
    cout<<"5555555555555555555555555555555555"<<endl;

    RenderState* r=new RenderState(
            true,
            GL_LEQUAL,
            false,
            GL_FRONT,
            GL_CCW,
            false,
            GL_FUNC_ADD,
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            false
    );
    mat->setPointerToRenderState(r);
    GameOverRenderer=new MeshRenderer(mp,mat);
    cout<<"6666666666666666666666666666666666666"<<endl;

}

void World::GameOver() {
    //Entities.clear();
    Entity *e = new Entity();
    e->addComponent(GameOverRenderer);
    Transform *t = new Transform(glm::vec3{-5, 0, 3},glm::vec3{0,0,0},glm::vec3{8,5,0.1});
    e->addComponent(t);
    e->setEntityName("GameOver");
    Entities.push_back(e);

}

void World::LoadGameWon(){
    our::ShaderProgram *pp = new our::ShaderProgram();
    cout<<"1111111111111111111111"<<endl;
    pp->create();
    pp->attach("assets/shaders/ex29_light/light_transform.vert", GL_VERTEX_SHADER);

    pp->attach("assets/shaders/ex32_textured_material/light_array.frag", GL_FRAGMENT_SHADER);

    pp->link();
    cout<<"222222222222222222222222"<<endl;

    our::Mesh* mp=new our::Mesh();
    cout<<"999999999999999999999999"<<endl;
    our::mesh_utils::loadOBJ(*mp,"assets/models/background/uploads_files_648761_cube.obj");
    cout<<"7777777777777777777"<<endl;
    Texture *tex = new Texture("assets/images/common/YouWon.jpg");
    cout<<"888888888888888888888888"<<endl;
    Material *mat=new Material(pp);
    cout<<"3333333333333333333333333"<<endl;

    mat->setPointerToEmissiveMap(tex);
    mat->setPointerToRoughnessMap(tex);
    mat->setPointerToAmbientOcuulsionMap(tex);
    mat->setPointerToSpecularMap(tex);
    mat->setPointerToAlbedoMap(tex);
    cout<<"444444444444444444444444444"<<endl;

    Sampler* s=new Sampler();
    mat->setPointerToSampler(s);
    mat->addUniform("alpha",1.0f);
    mat->addUniform("specular_tint",glm::vec3{1,1,1});
    mat->addUniform("emissive_tint",glm::vec3{1,1,1});
    mat->addUniform("albedo_tint",glm::vec3{1,1,1});
    mat->addUniform("roughness_range",glm::vec2{0,1});
    cout<<"5555555555555555555555555555555555"<<endl;

    RenderState* r=new RenderState(
            true,
            GL_LEQUAL,
            false,
            GL_FRONT,
            GL_CCW,
            false,
            GL_FUNC_ADD,
            GL_SRC_ALPHA,
            GL_ONE_MINUS_SRC_ALPHA,
            false
    );
    mat->setPointerToRenderState(r);
    GameWonRenderer=new MeshRenderer(mp,mat);
    cout<<"6666666666666666666666666666666666666"<<endl;

}

void World::GameWon() {
    //Entities.clear();
    Entity *e = new Entity();
    e->addComponent(GameWonRenderer);
    Transform *t = new Transform(glm::vec3{-5, 0, 3},glm::vec3{0,0,0},glm::vec3{8,5,0.1});
    e->addComponent(t);
    e->setEntityName("GameOver");
    Entities.push_back(e);

}

MeshRenderer* World::getBulletRenderer(){
    return bulletRenderer;
}
Entity* World::getScoreBarEntity()
{
    int Size=Entities.size();
    for(int i=0;i<Size;i++)
    {
        if(Entities.at(i) && Entities.at(i)->getEntityName()=="scorebar")
        {
            cout<<Entities.at(i)->getEntityName();
            return Entities[i];
        }
    }
    return nullptr;
}

World::~World() {

}