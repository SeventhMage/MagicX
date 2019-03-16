#version 330 core

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord0;

out vec3 normal;
out vec2 texCoord0;
out vec3 position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main()
{
	normal = normalize(mat3(viewMatrix * modelMatrix) * vNormal);	
	texCoord0 = vTexCoord0;
	vec4 pos = viewMatrix * modelMatrix * vPosition;
	position = pos.xyz;
	gl_Position = projMatrix * pos;
}


