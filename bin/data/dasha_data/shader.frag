#version 120

uniform vec2 osc;

void main(){
    
    vec2 st = gl_FragCoord.xy / osc/1000;
    // vec2 st = gl_FragCoord.xy / vec2(1024.0, 768.0);
    
    
    gl_FragColor = vec4(st.x,st.y,0.6,0.5);
}
