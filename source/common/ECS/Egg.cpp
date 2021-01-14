//
// Created by Aya on 1/14/2021.
//

#include "Egg.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"

#include "Components/CameraComponent.h"
#include "Components/Material.h"
#include "Components/Light.h"
Egg::Egg(glm::vec3 pos) {
    our::ShaderProgram *pp = new our::ShaderProgram();
    pp->create();
    pp->attach("assets/shaders/ex29_light/light_transform.vert", GL_VERTEX_SHADER);

    pp->attach("assets/shaders/ex32_textured_material/light_array.frag", GL_FRAGMENT_SHADER);

    pp->link();
    our::Mesh* mp=new our::Mesh();
    our::mesh_utils::loadOBJ(*mp,"assets/models/egg/egg.obj");
    Texture *tex = new Texture("assets/models/egg/Plastic010_1K_Color.jpg");
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
    MeshRenderer* meshRenderer=new MeshRenderer(mp,mat);
    addComponent(meshRenderer);
    Transform* t=new Transform(pos);
    addComponent(t);
    this->setEntityName("egg");
}