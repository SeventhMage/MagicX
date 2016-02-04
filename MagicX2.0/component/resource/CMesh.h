#ifndef _MX_RESOURCE_CMESH_H_
#define _MX_RESOURCE_CMESH_H_

#include <vector>

#include "mxDef.h"
#include "mxType.h"
#include "core/CVector3.h"
#include "core/CBoundingBox.h"
#include "resource/IMesh.h"
#include "render/IGPUBuffer.h"

namespace mx
{
	namespace resource
	{
		using namespace mx::core;

		typedef struct STriangle
		{
			uint state;	//状态信息
			uint attr;	//物理属性
			uint color;	//颜色

			CVector3 *vList;	//顶点列表
			uint indices[3];		//索引
		}Triangle, *PTriangle;


		class CMesh : public IMesh
		{
			friend class CPLXLoader;
		public:
			CMesh(render::IGPUBuffer *pGPUBuffer);
			virtual ~CMesh();

			virtual bool Load(const char *filename);
			virtual void rotateXZBy(double radians, const CVector3 &center = CVector3(0, 1.0f, 0));
			virtual void rotateXYBy(double radians, const CVector3 &center = CVector3(0, 0, 1.0f));
			virtual void rotateYZBy(double radians, const CVector3 &center = CVector3(1.0f, 0, 0));
			virtual void Update(uint deltaTime, const CMatrix4 &mat4VP);

			void CalculateBoundingBox();
			void CalculateRadius();
		private:
			void CreatePLXRenderable(uint idx);
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

			render::IGPUBuffer *m_pGPUBuffer;
			std::vector<render::IRenderableObject *> m_pRenderableObject;
		};
	}
}

#endif