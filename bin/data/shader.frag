
#version 120

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_smoothX;
uniform float u_smoothY;

void main(){
    
    vec2 hg = gl_FragCoord.xx / u_resolution;
    gl_FragColor = vec4(hg.x,hg.y,u_mouse.y/768,u_smoothX/1028);
}
