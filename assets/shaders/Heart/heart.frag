#version 330 core

// Here we will define Uniform Variable
// they are called uniform because every run of the shader (under the same draw call) will see the same value
// so it is uniform across all executions of the shader
uniform vec3 color;
uniform float time;
uniform bool flicker;
uniform vec2 translation;
//in vec2 translation;
// The output that goes to the frame buffer
out vec4 frag_color;
in vec3 position;


// Just a constant
#define PI 3.1415926535897932384626433832795

void main() {
    // Convert RGB to RGBA (in other words, add an alpha value).
    float x=translation.x+0.125;
    float y=translation.y+0.25;
    vec3 center1=vec3(x,y,0);
    x=translation.x-0.125;
    vec3 center2=vec3(x,y,0);
    if(position.y>=(translation.y+0.25)&&(distance(center1,position)<0.125||distance(center2,position)<0.125)){
        frag_color = vec4(color,1.0);
    }
    else if(position.y<(translation.y+0.25)&&position.y>(translation.y-0.25)&&position.y-translation.y+0.25>2*position.x-2*translation.x&&
    position.y-translation.y+0.25>-2*position.x+2*translation.x){
        frag_color = vec4(color,1.0);
    }
    else{
        frag_color = vec4(0,0,0,1.0);
    }

    // If flickering, multiply it with a sinusoidal wave that oscillates over time
    if(flicker)
        frag_color.rgb *= 0.5 * (1 + cos(2 * PI * time));
}
