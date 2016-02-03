#ifndef _MX_RESOURCE_CMESH_H_
#define _MX_RESOURCE_CMESH_H_

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
			int state;	//״̬��Ϣ
			int attr;	//��������
			int color;	//��ɫ

			CVector3 *vList;	//�����б�
			int indices[3];		//����
		}Triangle, *PTriangle;


		class CMesh : public IMesh
		{
			friend class CPLXLoader;
		public:
			CMesh(render::IGPUBuffer *pGPUBuffer);
			virtual ~CMesh();

			virtual bool Load(const char *filename);

			virtual byte *GetVerticesData() const;
			virtual uint GetVerticesSize() const;
			virtual uint GetVerticesCount() const;
			virtual uint GetVertexStride() const;
			virtual byte *GetIndicesData() const;
			virtual uint GetIndicesSize() const;
			virtual uint GetIndicesCount() const;

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

			CVector3 m_vWorldPos;		//������λ��
			CVector3 m_vDir;
			CVector3 m_vUx, m_vUy, m_vUz;

			uint m_uVerticesNum;
			CVector3 *m_pvLocalList;
			CVector3 *m_pvTransList;

			uint m_uTriangleNum;
			Triangle *m_pTriangleList;

			float *m_pVerticesData;
			int *m_pIndecisData;

			render::IGPUBuffer *m_pGPUBuffer;
		};
	}
}

#endif