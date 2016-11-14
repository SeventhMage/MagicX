#version 330 core

attribute vec3 vVertex;
uniform mat4 mvpMatrix;
varying vec3 vVaryingTexCoord;

void main()
{
	vVaryingTexCoord = normalize(vVertex);
	gl_Position = mvpMatrix * vec4(vVertex.xyz, 1.0f);
}