#ifndef _MX_RESOURCE_CMESH_H_
#define _MX_RESOURCE_CMESH_H_

#include "mxDef.h"
#include "mxType.h"
#include "core/CVector3.h"
#include "core/CBoundingBox.h"
#include "resource/IMesh.h"

namespace mx
{
	namespace resource
	{
		using namespace mx::core;

		typedef struct STriangle
		{
			int state;	//状态信息
			int attr;	//物理属性
			int color;	//颜色

			CVector3 *vList;	//顶点列表
			int indices[3];		//索引
		}Triangle, *PTriangle;


		class CMesh : public IMesh
		{
			friend class CPLXLoader;
		public:
			CMesh();
			virtual ~CMesh();

			void CalculateBoundingBox();
			void CalculateRadius();
		private:
			uint m_uId;
			char m_szName[MAX_FILE_NAME];
			uint m_uState;
			uint m_uAttr;

			CBoundingBox m_boundingBox;
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