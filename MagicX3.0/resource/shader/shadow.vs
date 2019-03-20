#version 130

in vec4 vVertex;

uniform mat4 modelMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjMatrix;

void main()
{
	gl_Position = lightProjMatrix * lightViewMatrix * modelMatrix * vVertex;
}
