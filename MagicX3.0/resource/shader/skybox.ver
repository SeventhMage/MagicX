#version 330 core

attribute vec3 vPosition;
uniform mat4 mvpMatrix;
varying vec3 vVaryingTexCoord;

void main()
{
	vVaryingTexCoord = normalize(vPosition);
	gl_Position = mvpMatrix * vec4(vPosition.xyz, 1.0f);
}