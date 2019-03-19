#version 330 core

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexCoord0;

out vec3 normal;
out vec2 texCoord0;
out vec3 position;

uniform mat4 modelMatrix;
uniform mat4 lightViewMatrix;
uniform mat4 lightProjMatrix;

void main()
{
	normal = normalize(mat3(lightViewMatrix * modelMatrix) * normalize(vNormal));	
	texCoord0 = vTexCoord0;
	vec4 pos = lightViewMatrix * modelMatrix * vPosition;
	position = pos.xyz;
	gl_Position = lightProjMatrix * pos;
}


