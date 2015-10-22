#version 330 core

//varying vec4 color;
varying vec2 vTex;
uniform sampler2D textureUnit0;

void main()
{
	//gl_FragColor = color;
	
	gl_FragColor = texture2D(textureUnit0, vTex);
}