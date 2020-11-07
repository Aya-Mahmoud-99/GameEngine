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
    float r1=0.25; // face circle
    float r2=0.11; // mouse half circle
    float r2th=0.14;
    float r3=0.04; // eye circle
    float r4=0.04; // eye circle
    float x=translation.x;
    float y=translation.y;
    vec3 center1=vec3(x,y,0); // for face circle & mouse half circle
    float y2=y+0.11;
    float x2=x+r2;
    vec3 center3=vec3(x2,y2,0); //right eye
    float x3=x-r2;
    vec3 center4=vec3(x3,y2,0); //left eye

    if((distance(center1,position) > r1) || (distance(center3,position) < r3) || (distance(center4,position) < r4) || (distance(center1,position) > r2 && distance(center1,position) < r2th && distance(center3,position)>0.115 && distance(center4,position)>0.115 ))
    {
        frag_color = vec4(0,0,0,1.0);
    }
    else{
        frag_color = vec4(color, 1.0);
    }
    //frag_color = vec4(color, 1.0);

    // If flickering, multiply it with a sinusoidal wave that oscillates over time
    if(flicker)
        frag_color.rgb *= 0.5 * (1 + cos(2 * PI * time));
}
