/************************************************************************/
/* 渲染列表                                                             */
/************************************************************************/

#ifndef _MX_RENDER_C_RENDER_QUEUE_H_
#define _MX_RENDER_C_RENDER_QUEUE_H_

#include "render/IRenderList.h"
#include "render/IVertexArrayObject.h"

#include <list>

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
			virtual void RemoveRenderable(IRenderable *pRenderable);
			virtual void Render();

		private:
			std::list<IRenderable *> m_renderableList;			//渲染列表
		};

	}
}

#endif