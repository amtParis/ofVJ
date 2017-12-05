#version 120

varying vec4 globalColor;

uniform float change;
uniform sampler2DRect tex0;

//varying vec2 texCoordVarying;


void main()
{
    // vec4 color;
    // globalColor is being set inside the vertex shader.
    // the fragment color is then set to the globalColor.
    gl_FragColor = globalColor;
    
    //gl_FragColor = texture2DRect(tex0, texCoordVarying+sin(change));
}

