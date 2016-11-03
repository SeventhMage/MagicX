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
			CRenderable();
			virtual ~CRenderable();

			virtual void SumbitToRenderQueue();
			virtual void Render();
			virtual void Bind();
		private:
			IRenderList *m_pRenderQueue;				//当前渲染队列
			IBufferObject *m_pVBO;						//顶点缓冲区对象
			IBufferObject *m_pIBO;						//索引缓冲区对象

			ITexture *m_pTexture[TU_TEXTURE_NUM];		//纹理

			CShaderProgram *m_pShaderProgram;			//shader程序
		};
	}
}

#endif