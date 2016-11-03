/************************************************************************/
/* ��С��Ⱦʵ��ʵ��                                                     */
/************************************************************************/

#ifndef _MX_RENDER_C_RENDERABLE_H_
#define _MX_RENDER_C_RENDERABLE_H_

#include "render/IRenderable.h"
#include "render/ITexture.h"
#include "render/IRenderList.h"

#include "CShaderProgram.h"

namespace mx
{
	namespace render
	{
		class CRenderable : public IRenderable
		{
		public:
			CRenderable(IRenderList *pRenderList);
			virtual ~CRenderable();

			virtual IBufferObject *GetVertexBufferObject() { return m_pVBO; }
			virtual IBufferObject *GetIndexBufferObject() { return m_pIBO; }

			virtual void SetActive(bool bActive) { m_bActive = bActive; }
			virtual bool IsActive() { return m_bActive; }

			virtual void SumbitToRenderQueue();
			virtual void Bind();

		private:
			IRenderList *m_pRenderList;					//��ǰ��Ⱦ����
			IBufferObject *m_pVBO;						//���㻺��������
			IBufferObject *m_pIBO;						//��������������

			ITexture *m_pTexture[TU_TEXTURE_NUM];		//����

			CShaderProgram *m_pShaderProgram;			//shader����

			bool m_bActive;
		};
	}
}

#endif