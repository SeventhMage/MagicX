#include "Cube.h"

CubeVertex::CubeVertex()
:halfWide(5)
{

	float vertice[] = {
		//front
		-halfWide, -halfWide, halfWide, 0, 0, -halfWide, -halfWide, halfWide,
		halfWide, -halfWide, halfWide, 1, 0, halfWide, -halfWide, halfWide,
		halfWide, halfWide, halfWide, 1, 1, halfWide, halfWide, halfWide,
		-halfWide, halfWide, halfWide, 0, 1,-halfWide, halfWide, halfWide,

		//back
		halfWide, -halfWide, -halfWide, 0, 0, halfWide, -halfWide, -halfWide, 
		-halfWide, -halfWide, -halfWide, 1, 0,-halfWide, -halfWide, -halfWide,
		-halfWide, halfWide, -halfWide, 1, 1,-halfWide, halfWide, -halfWide,
		halfWide, halfWide, -halfWide, 0, 1,halfWide, halfWide, -halfWide,

		//left
		-halfWide, -halfWide, -halfWide, 0, 0,-halfWide, -halfWide, -halfWide,
		-halfWide, -halfWide, halfWide, 1, 0,-halfWide, -halfWide, halfWide,
		-halfWide, halfWide, halfWide, 1, 1,-halfWide, halfWide, halfWide,
		-halfWide, halfWide, -halfWide, 0,1,-halfWide, halfWide, -halfWide,

		//right
		halfWide, -halfWide, halfWide, 0, 0,halfWide, -halfWide, halfWide,
		halfWide, -halfWide, -halfWide, 1, 0,halfWide, -halfWide, -halfWide,
		halfWide, halfWide, -halfWide, 1, 1,halfWide, halfWide, -halfWide,
		halfWide, halfWide, halfWide, 0, 1,halfWide, halfWide, halfWide,

		//top
		-halfWide, halfWide, halfWide, 0, 0,-halfWide, halfWide, halfWide, 
		halfWide, halfWide, halfWide, 1, 0, halfWide, halfWide, halfWide,
		halfWide, halfWide, -halfWide, 1, 1, halfWide, halfWide, -halfWide,
		-halfWide, halfWide, -halfWide, 0, 1, -halfWide, halfWide, -halfWide,

		//bottom
		-halfWide, -halfWide, -halfWide, 0, 0,-halfWide, -halfWide, -halfWide,
		halfWide, -halfWide, -halfWide, 1, 0,halfWide, -halfWide, -halfWide,
		halfWide, -halfWide, halfWide, 1, 1,halfWide, -halfWide, halfWide,
		-halfWide, -halfWide, halfWide, 0, 1,-halfWide, -halfWide, halfWide, 

	};
	m_verCount = sizeof(vertice) / sizeof(float);
	m_cubeVertex = new float[m_verCount];

	uint indice[] = {
		//front
		0, 1, 2,
		0, 2, 3,

		//back
		4, 5, 6,
		4, 6, 7,

		//left
		8, 9, 10,
		8, 10, 11,

		//right
		12, 13, 14,
		12, 14, 15,

		//top
		16, 17, 18,
		16, 18, 19,

		//bottom
		20, 21, 22,
		20, 22, 23,
	};
	m_indiceCount = sizeof(indice) / sizeof(uint);
	m_cubeIndices = new uint[m_indiceCount];
	memcpy(m_cubeVertex, vertice, sizeof(vertice));
	memcpy(m_cubeIndices, indice, sizeof(indice));
}

CubeVertex::~CubeVertex()
{
	delete[]m_cubeVertex;
	delete[]m_cubeIndices;
}

mx::scene::EVertexAttribute CubeVertex::GetVertexAttribute()
{
	return EVertexAttribute(VF_POSITION | VF_TEXCOORD | VF_NORMAL);
}
