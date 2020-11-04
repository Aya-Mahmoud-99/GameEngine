#version 330 core

uniform vec2 scale;
uniform vec2 translation;

uniform float time;
uniform bool vibrate;
out vec3 position;

#define PI 3.1415926535897932384626433832795

void main() {
    
    const vec3 positions[12] = vec3[12](
    //First upper triangle
    vec3(0.0, 0.0, 0.0),
    vec3(-0.25, 0.25, 0.0),
    vec3( 0.25, 0.25, 0.0),
    //Second big triangle contains left and lower traingle
    vec3( -0.25,0.25, 0.0),
    vec3( 0.25,-0.25, 0.0),
    vec3( -0.25,-0.25, 0.0),
    //Third small uppertriangle for the eye
    vec3( 0.0,0.0625, 0.0),
    vec3( 0.0,0.1875, 0.0),
    vec3( -0.125,0.1875, 0.0),
    //Fourth small lowertriangle for the eye
    vec3( 0.0,0.0625, 0.0),
    vec3( -0.125,0.0625, 0.0),
    vec3( -0.125,0.1875, 0.0)
    );

    // get the position based on the vertex id
    position = positions[gl_VertexID];
    // Scale it
    position.xy *= scale;
    // If vibrate is on, scale it with a sinusoidal wave that oscillates over time
    if(vibrate)
        position.xy *= 1 + 0.1 * sin(2 * PI * time);
    // Translate it
    position.xy += translation;

    // Finally send the value to "gl_Position".
    gl_Position = vec4(position, 1.0);
}