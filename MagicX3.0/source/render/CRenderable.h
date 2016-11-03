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
			CRenderable();
			virtual ~CRenderable();

			virtual void SumbitToRenderQueue();
			virtual void Render();
			virtual void Bind();
		private:
			IRenderList *m_pRenderQueue;				//��ǰ��Ⱦ����
			IBufferObject *m_pVBO;						//���㻺��������
			IBufferObject *m_pIBO;						//��������������

			ITexture *m_pTexture[TU_TEXTURE_NUM];		//����

			CShaderProgram *m_pShaderProgram;			//shader����
		};
	}
}

#endif