#ifndef _MX_CUBE_H_
#define _MX_CUBE_H_

#include "mx.h"

using namespace mx;

class CubeVertex : public IVertex
{
public:
	CubeVertex();
	virtual ~CubeVertex();

	virtual EVertexAttribute GetVertexAttribute();
	virtual void *GetVertexData() { return m_cubeVertex; }
	virtual uint GetVerticeCount() { return 40; }
	virtual uint GetVerticeSize() { return 40 * sizeof(float); }
	virtual void *GetIndicesData() { return m_cubeIndices; }
	virtual uint GetIndicesCount() { return 36; }
private:
	float *m_cubeVertex;
	uint *m_cubeIndices;
	float halfWide;
};

#endif