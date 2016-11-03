/************************************************************************/
/* 渲染列表                                                             */
/************************************************************************/

#ifndef _MX_RENDER_C_RENDER_QUEUE_H_
#define _MX_RENDER_C_RENDER_QUEUE_H_

#include <list>

#include "render/IRenderList.h"
#include "render/IRenderable.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace render
	{
		class CRenderList : public IRenderList
		{
		public:
			CRenderList();
			virtual ~CRenderList();

			virtual void AddRenderable(IRenderable *pRenderable);
			virtual void BeginRender();
			virtual void Render();
			virtual int GetRenderableCount();
			virtual RENDER_LIST &GetRenderList();

		private:
			RENDER_LIST m_renderableList;			//渲染队列
		};

	}
}

#endif