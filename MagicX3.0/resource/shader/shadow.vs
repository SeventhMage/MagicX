#version 130

in vec4 vVertex;

uniform mat4 modelMatrix;
uniform mat4 viewLightMatrix;
uniform mat4 projLightMatrix;

void main()
{
	gl_Position = projLightMatrix * viewLightMatrix * modelMatrix * vVertex;
}
