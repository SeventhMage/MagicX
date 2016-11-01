#version 330 core

attribute vec4 vPosition;
attribute vec2 vTexCoord0;

varying vec2 vTex;

uniform mat4 mvpMatrix;

void main()
{
	gl_Position = mvpMatrix * vPosition;
	
	vTex = vTexCoord0;
}