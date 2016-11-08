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
	virtual uint GetVerticeCount() { return (96); }
	virtual uint GetVerticeSize() { return (96) * sizeof(float); }
	virtual void *GetIndicesData() { return m_cubeIndices; }
	virtual uint GetIndicesCount() { return 36; }
	virtual void *GetTexCoordData() { return m_texCoord; }
	virtual uint GetTexCoordCount() { return 12 * 6; };
	virtual uint GetTexCoordSize() { return 12 * 6 * sizeof(float); }
private:
	float *m_cubeVertex;
	float *m_texCoord;
	uint *m_cubeIndices;
	float halfWide;
};

#endif