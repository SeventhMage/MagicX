/************************************************************************/
/* ����������������ݽ�Ϲ��ɿ���Ⱦ����                               */
/************************************************************************/
#ifndef _MX_C_REFLECT_OBJECT_H_
#define _MX_C_REFLECT_OBJECT_H_

#include "render/IVertexArrayObject.h"
#include "render/ITexture.h"
#include "render/IRenderable.h"

namespace mx
{
	namespace scene
	{
		using namespace render;
		class CReflectObject
		{
		public:
			CReflectObject();
			~CReflectObject();
			
			/************************************************************************/
			/* ͨ������Ķ����뷨�����ݣ�������������pTexture�ķ���                 */
			/************************************************************************/
			void Create(void *pVertexes, void *pNormals, int vertSize, int verticeCount, ITexture *pTexture);

			void Update(const float mvpMat4[16], const float mvMat4[16], const float camInvMat4[16], const float normalMat3[9]);
			void Render();
		private:
			IVertexArrayObject *m_pVAO;
			IRenderable *m_pRenderable;
		};
	}
}

#endif