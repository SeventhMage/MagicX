#ifndef _MX_RESOURCE_CMESH_H_
#define _MX_RESOURCE_CMESH_H_

#include <vector>

#include "mxDef.h"
#include "mxType.h"
#include "core/CVector3.h"
#include "resource/IMesh.h"

namespace mx
{
	namespace resource
	{
		using namespace mx::core;
		class CMesh : public IMesh
		{
			friend class CPLXLoader;
		public:
			CMesh();
			virtual ~CMesh();

			virtual bool Load(const char *filename);
			virtual void rotateXZBy(double radians, const CVector3 &center = CVector3(0, 1.0f, 0));
			virtual void rotateXYBy(double radians, const CVector3 &center = CVector3(0, 0, 1.0f));
			virtual void rotateYZBy(double radians, const CVector3 &center = CVector3(1.0f, 0, 0));

			virtual const CVector3 &GetWorldPosition() const { return m_vWorldPos; }
			virtual const float GetMaxRadius() const { return m_fMaxRadius; }

			virtual Triangle *GetTrianglesList() const { return m_pTriangleList; }
			virtual CVector3 *GetVertices() const { return m_pvLocalList; }
			virtual uint GetVerticesNum() const { return m_uVerticesNum; }
			virtual uint GetTrianglesNum() const { return m_uTriangleNum; }
			void CalculateRadius();

		private:
			uint m_uId;
			char m_szName[MAX_FILE_NAME];
			uint m_uState;
			uint m_uAttr;

			float m_fAvgRadius;
			float m_fMaxRadius;

			CVector3 m_vWorldPos;		//世界中位置
			CVector3 m_vDir;
			CVector3 m_vUx, m_vUy, m_vUz;

			uint m_uVerticesNum;
			CVector3 *m_pvLocalList;
			CVector3 *m_pvTransList;

			uint m_uTriangleNum;
			Triangle *m_pTriangleList;
		};
	}
}

#endif