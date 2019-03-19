#version 130

in vec4 vVertex;

uniform int index;

uniform mat4 modelMatrix[64];
uniform mat4 viewLightMatrix[64];
uniform mat4 projLightMatrix[64];

void main()
{
	gl_Position = projLightMatrix[index] * viewLightMatrix[index] * modelMatrix[index] * vVertex;
}
