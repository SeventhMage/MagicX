#version 330 core

in vec3 vPosition;
uniform mat4 mvpMatrix;
out vec3 vVaryingTexCoord;

void main()
{
	vVaryingTexCoord = normalize(vPosition);
	gl_Position = mvpMatrix * vec4(vPosition.xyz, 1.0f);
}