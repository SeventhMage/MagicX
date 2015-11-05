#version 330 core

uniform sampler2D textureUnit0;
varying vec4 color;
varying vec2 vTex;


void main()
{	
	//gl_FragColor = color;
	gl_FragColor = texture2D(textureUnit0, vTex);
}