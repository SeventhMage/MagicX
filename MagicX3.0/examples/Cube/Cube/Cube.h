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
	virtual uint GetVerticeCount() { return (m_verCount); }
	virtual uint GetVerticeSize() { return (m_verCount)* sizeof(float); }
	virtual void *GetIndicesData() { return m_cubeIndices; }
	virtual uint GetIndicesCount() { return m_indiceCount; }
private:
	float *m_cubeVertex;
	uint *m_cubeIndices;
	float halfWide;
	uint m_verCount;
	uint m_indiceCount;
};

#endif