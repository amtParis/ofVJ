#version 120

varying vec4 globalColor;
uniform float scaledVol;

void main(){
    
    vec4 position = gl_ModelViewProjectionMatrix * gl_Vertex;
    float displacementY = sin(scaledVol + (position.x/100.0)) * 80.0;
    position.y += displacementY;
    
    //    position.y += sin(position.x / 30.0) * 100.0;
    gl_Position = position;
    globalColor = gl_Color;
    
    
}

