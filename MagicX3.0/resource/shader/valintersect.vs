#version 130

in vec4 vVertex;

uniform int index;

uniform mat4 modelMatrix[64];
uniform mat4 lightViewMatrix[64];
uniform mat4 lightProjMatrix[64];

void main()
{
	gl_Position = lightProjMatrix[index] * lightViewMatrix[index] * modelMatrix[index] * vVertex;
}
