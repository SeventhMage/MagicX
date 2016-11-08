#include "Cube.h"

CubeVertex::CubeVertex()
:halfWide(5)
{

	float vertice[] = {
		//position
		-halfWide, -halfWide, halfWide,
		halfWide, -halfWide, halfWide,
		halfWide, halfWide, halfWide,
		-halfWide, halfWide, halfWide,

		-halfWide, -halfWide, -halfWide,
		halfWide, -halfWide, -halfWide,
		halfWide, halfWide, -halfWide,
		-halfWide, halfWide, -halfWide,

		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1,

		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1,

		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1,

		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1,

		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1,

		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1
	};

	m_cubeVertex = new float[sizeof(vertice) / sizeof(float)];

	uint indice[] = {
		//front
		0, 1, 2,
		0, 2, 3,

		//back
		5, 4, 7,
		5, 7, 6,

		//left
		4, 0, 3,
		4, 3, 7,

		//right
		1, 5, 6,
		1, 6, 2,

		//top
		3, 2, 6,
		3, 6, 7,

		//bottom
		1, 0, 4,
		1, 4, 5,
	};
	m_cubeIndices = new uint[sizeof(indice) / sizeof(uint)];
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
	return EVertexAttribute(VF_POSITION | VF_TEXCOORD);
}
