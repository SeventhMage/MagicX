/************************************************************************/
/* 球体数学创建                                                         */
/************************************************************************/

#ifndef _MX_SCENE_C_SPHERE_H_
#define _MX_SCENE_C_SPHERE_H_

#include "math/CVector3.h"
#include "math/CVector2.h"

namespace mx
{
	namespace scene
	{
		class CSphere
		{
		public:
			CSphere(float fRadius, int iSlices, int iStacks);
			~CSphere();

			math::CVector3 *GetVertices() { return m_vertices; }
			math::CVector3 *GetNormals() { return m_normals; }
			math::CVector2 *GetTexCoords() { return m_texCoords; }
			int GetVertexCount() { return m_vertexCount; }
			int GetVertexSize() { return m_vertexCount * sizeof(math::CVector3); }

		private:
			math::CVector3 *m_vertices;
			math::CVector3 *m_normals;
			math::CVector2 *m_texCoords;
			int m_vertexCount;
		};
	}
}

#endif