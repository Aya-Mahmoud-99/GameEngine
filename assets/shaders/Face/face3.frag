#version 330 core


uniform vec3 color;
uniform float time;
uniform bool flicker;
uniform vec2 translation;

out vec4 frag_color;
in vec3 position;


// Just a constant
#define PI 3.1415926535897932384626433832795

void main() {
    float radius1=0.25;
    float radius2=0.0625;
    float x=translation.x;
    float y=translation.y;
    vec3 center1=vec3(x,y,0);
    float y2=y+0.125;
    vec3 center2=vec3(x,y2,0);
    float x5=position.x-translation.x;
    float y5=position.y-translation.y;
    vec2 V=vec2(-y5,x5);
    float ResV_L=-1*y5-x5;
    float ResV_R=x5-y5;

    if((distance(center1,position)>radius1 &&distance(center1,position)>radius1 ) || distance(center2,position)<radius2 || (ResV_L<0 && ResV_R>0)){
        frag_color = vec4(0,0,0,1.0);
    }
    else{
        frag_color = vec4(color, 1.0);
    }
    // If flickering, multiply it with a sinusoidal wave that oscillates over time
    if(flicker)
        frag_color.rgb *= 0.5 * (1 + cos(2 * PI * time));
}