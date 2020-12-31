//
// Created by Aya on 12/18/2020.
//

#include "Sampler.h"
our::WindowConfiguration Sampler::getWindowConfiguration() {
return { "Sampler Objects", {1280, 720}, false };
}
Sampler::Sampler(Transform*tran){
    glGenSamplers(1, &sampler);
}
void Sampler::SamplerBind(our::ShaderProgram *p,int unit){
   // glBindSampler(0, sampler);
   // p->set("sampler", 0);
    // Now, instead of setting the parameters for each texture, we just set it to the sampler and each unit that uses that sampler will automatically use these parameters.
    glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, magnification_filter);
    glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, minification_filter);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, wrap_s);
    glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, wrap_t);
    glSamplerParameterfv(sampler, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(border_color));
    glSamplerParameterf(sampler, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
    glBindSampler(unit, sampler);


}
Sampler::~Sampler(){
    glDeleteSamplers(1, &sampler);
}
