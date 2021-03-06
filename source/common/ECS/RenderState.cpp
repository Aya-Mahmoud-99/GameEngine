//
// Created by BasantLoay on 12/24/2020.
//

#include "RenderState.h"
#include <iostream>
using namespace std;
RenderState::RenderState(bool depthEnable,GLenum dpFun,bool cullEnable,GLenum cullface,GLenum frontwinding,bool blendEnable,GLenum blendFun,GLenum source,GLenum dest,bool transparent1){
     enable_depth_test = depthEnable;
     depth_function = dpFun;
     enable_face_culling = cullEnable;
     culled_face =cullface;
     front_face_winding = frontwinding;
     enable_blending=blendEnable;
     blend_equation =blendFun;
     blend_source_factor=source;
     blend_destination_factor=dest;
     cout<<"dest"<<dest<<endl;
     transparent=transparent1;
}

void RenderState::DepthTesting(){
    if(enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);       // This line enables depth testing.
    glDepthFunc(depth_function);

   glClearDepth(clear_depth);                              // Specifies the depth value used when the depth buffer is cleared. The initial value is 1.

    glDepthMask(depth_mask);
    glColorMask(color_mask.r, color_mask.g, color_mask.b, color_mask.a);

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clearing the depth buffer is important now as we are drawing to it each frame.
}
void RenderState::Culling(){
    if(enable_face_culling) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);       // This line enables face culling.
    glCullFace(culled_face);
    glFrontFace(front_face_winding);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void RenderState::Blending(){

    glBlendEquation(blend_equation);
    //cout<<blend_equation<<endl;
    glBlendFunc(blend_source_factor, blend_destination_factor);
   // cout<<"sssssssssss"<<blend_source_factor<<endl;
 //   cout<<blend_destination_factor<<endl;

    glBlendColor(blend_constant_color.r, blend_constant_color.g, blend_constant_color.b, blend_constant_color.a);
    //glBlendEquation(GL_FUNC_ADD);
   // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendColor(1.0f,1.0f,1.0f,1.0f);
    if(transparent && enable_blending) glEnable(GL_BLEND);
    else glDisable(GL_BLEND);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
our::WindowConfiguration RenderState::getWindowConfiguration() {
    return { "RenderState:DepthTesting,Culling,Blending", {1280, 720}, false };
}

void RenderState::setTransparency(bool transparent1){
    transparent=transparent1;
}
///////////////////////
bool RenderState::getTransparency(){
    return transparent;
}