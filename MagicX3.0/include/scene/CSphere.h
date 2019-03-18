/************************************************************************/
/* 球体数学创建                                                         */
/************************************************************************/

#ifndef _MX_SCENE_C_SPHERE_H_
#define _MX_SCENE_C_SPHERE_H_

#include "math/CVector3.h"
#include "math/CVector2.h"
#include "IMesh.h"

namespace mx
{
	namespace scene
	{
		class CSphere : public IMesh
		{
		public:
			CSphere(float fRadius, int iSlices, int iStacks);
			~CSphere();

			virtual bool Intersect(const math::CRay &ray, const math::CMatrix4 &transform, float *distance = nullptr, math::CVector3 *hitPoint = nullptr, math::CVector2 *uv = nullptr, uint *triIndex = nullptr);
			virtual void GetSurfaceData(const uint &triIndex, const math::CVector2 &uv, math::CVector3 &hitNormal, base::Color &hitColor);

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