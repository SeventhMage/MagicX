#version 330 core

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord0;

out vec3 normal;
out vec2 texCoord0;
out vec3 position;

uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;


void main()
{
	normal = normalMatrix * vNormal;
	texCoord0 = vTexCoord0;
	gl_Position = mvpMatrix * vPosition;
	position = gl_Position.xyz;
}


