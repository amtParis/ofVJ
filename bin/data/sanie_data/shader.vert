#version 120

varying vec4 globalColor;
//TEXTURE
varying vec2 texCoordVarying;
uniform sampler2DRect tex0;

// the time value is passed into the shader by the OF app.
uniform float time;

void main()
{
    vec4 vertex = gl_Vertex;
    vec4 position = gl_ModelViewProjectionMatrix * gl_Vertex;

// get the texture coordinates
    texCoordVarying = gl_MultiTexCoord0.xy;
    
    vec4 modifiedPosition = gl_Vertex;
	vec3 normal = (gl_NormalMatrix * gl_Normal);
    
    // we need to scale up the values we get from the texture
    float scale = 200;
    
    // here we get the red channel value from the texture
    // to use it as vertical displacement
    float displacementY = texture2DRect(tex0, texCoordVarying).x;
		
    // use the displacement we created from the texture data
    // to modify the vertex position
    modifiedPosition.xyz += displacementY * scale * normal * (sin(time));

    // this is the resulting vertex position multiplied by the correct matrix
	gl_Position = gl_ModelViewProjectionMatrix * modifiedPosition;
    
    // in OpenGL 2.0 we must get the global color using the gl_Color command,
    // and store it in a globalColor (varying) that is passed to our frag shader.
    // please note that the frag shader also has a globalColor (varying),
    // and this is the standard way of passing data from the vertex shader to the frag shader.
    globalColor = gl_Color;
}

