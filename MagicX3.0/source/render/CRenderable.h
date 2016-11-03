/************************************************************************/
/* 最小渲染实体实现                                                     */
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
			IRenderList *m_pRenderList;					//当前渲染队列
			IBufferObject *m_pVBO;						//顶点缓冲区对象
			IBufferObject *m_pIBO;						//索引缓冲区对象

			ITexture *m_pTexture[TU_TEXTURE_NUM];		//纹理

			CShaderProgram *m_pShaderProgram;			//shader程序

			bool m_bActive;
		};
	}
}

#endif