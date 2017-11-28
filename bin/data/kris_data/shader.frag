#version 120

uniform vec2 u_resolution;
uniform float u_time;
float floaty;


void main(){
    //    vec2 st = gl_FragCoord.xy / 1024.0;
    //
    //    //gl_FragColor = vec4(1.0,0.4,0.6,1.0);
    //    gl_FragColor = vec4(st.x,0.4,0.6,1.0);
    
//    vec2 st = gl_FragCoord.xy / u_resolution / 2;
//    gl_FragColor = vec4(st.x,st.x,0.1,0.5);
    
    //vec2 st = gl_FragCoord.xy/u_resolution + (0.7, -0.3);
    
//    floaty = u_time * 0.008;
    
    floaty = abs(sin(u_time)) - 1.0;
    vec2 st = gl_FragCoord.xy/u_resolution - floaty;

    
    float y = pow(st.x,500.0);
    
    vec2 color = vec2(y);
    color.x = color.x + .9;
    color.y = color.y + .25;
    //color.z = color.z + .1;
    gl_FragColor = vec4(color,0.54, 1.0);
}
