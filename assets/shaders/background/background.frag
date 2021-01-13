// Original by Alexander Lemke, 2015
// Voronoi function based on function from iq
// Simplified as a space background for games by dax105, 2018

//#define SHOW_CELLS
//#define USE_VORONOI
#define STAR_LAYER_COUNT 10

uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;                 // shader playback time (in seconds)
uniform float     iTimeDelta;            // render time (in seconds)
uniform int       iFrame;                // shader playback frame
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
//uniform samplerXX iChannel 0..3;          // input channel. XX = 2D/Cube
uniform vec4      iDate;                 // (year, month, day, time in seconds)
uniform float     iSampleRate;           // sound sample rate (i.e., 44100)

vec2 hash(in vec2 p) {
	return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

vec2 hash22(vec2 p)
{
	vec3 p3 = fract(vec3(p.xyx) * vec3(.1031, .1030, .0973));
    p3 += dot(p3, p3.yzx+19.19);
    return fract((p3.xx+p3.yz)*p3.zy);
}

float noise(in vec2 p) {
    #ifdef USE_VORONOI
    
    vec2 n = floor(p);
    vec2 f = fract(p);

    vec2 mg, mr;

    float md = 8.0;
    for(int j = -1; j <= 1; ++j) {
        for(int i = -1; i <= 1; ++i) {
            vec2 g = vec2(float(i), float(j));
            vec2 o = hash22(n + g);

            vec2 r = g + o - f;
            float d = dot(r, r);

            if(d < md) {
                md = d;
                mr = r;
                mg = g;
            }
        }
    }
    return md;
    
    #else
    
    vec2 n = floor(p);
    vec2 f = fract(p);

    float md = 1.0;

    // Scale a bit to move from cell edges
    vec2 o = hash22(n)*0.96 + 0.02;

    vec2 r = o - f;
    float d = dot(r, r);

    md = min(d, md);

    return md;
    
    #endif
}

vec3 starfield(vec2 samplePosition, float threshold) {
    float starValue = noise(samplePosition);
    
    float power = max(1.0 - (starValue / threshold), 0.0);
    power = power * power * power;
    
    #ifdef SHOW_CELLS
    power += starValue;
    #endif
    
    return vec3(power);
}


void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    float maxResolution = max(iResolution.x, iResolution.y);
    
	vec3 finalColor;
    vec2 sCoord = (fragCoord.xy / maxResolution)*5.0;
    vec2 pos = vec2(iTime*5.0, sin(iTime)*5.0);
    
    // Add starfields
    for (int i = 1; i <= STAR_LAYER_COUNT; i++) {
        float fi = float(i);
        float inv = sqrt(1.0/fi);
    	finalColor += starfield((sCoord + vec2(fi*100.0, -fi*50.0)) * (1.0 + fi * 0.2) + pos, 0.0005)*inv;
    }
    
    fragColor = vec4(finalColor, 1.0);
}