#version 330 core

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord0;

out vec3 vOutNormal;
out vec2 vOutTexCoord0;

uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;


void main()
{
	vOutNormal = normalMatrix * vNormal;
	vOutTexCoord0 = vTexCoord0;
	gl_Position = mvpMatrix * vPosition;
}


