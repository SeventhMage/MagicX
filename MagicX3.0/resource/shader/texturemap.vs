#version 330 core

in vec3 vPosition;
in vec2 vTexCoord0;

out vec2 vOutTexCoord0;

void main()
{
	vOutTexCoord0 = vTexCoord0;
	gl_Position = vec4(vPosition, 1.0);
}


