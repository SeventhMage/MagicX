#version 330 core

in vec3 vVertex;
uniform mat4 mvpMatrix;
out vec3 vVaryingTexCoord;

void main()
{
	vVaryingTexCoord = normalize(vVertex);
	gl_Position = mvpMatrix * vec4(vVertex.xyz, 1.0f);
}