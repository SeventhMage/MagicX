/************************************************************************/
/* 渲染列表接口                                                         */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDER_QUEUE_H_
#define _MX_RENDER_I_RENDER_QUEUE_H_

#include "IRenderable.h"

#include <list>

namespace mx
{
	namespace render
	{
		typedef std::list<IRenderable *> RENDER_LIST;

		class IRenderList
		{
		public:			
			virtual ~IRenderList(){}
			
			//添加渲染实体到渲染列表
			virtual void AddRenderable(IRenderable *pRenderable) = 0;
			//移除渲染实体
			virtual void RemoveRenderable(IRenderable *pRenderable) = 0;
			
			//执行渲染
			virtual void Render(IRenderer *pRenderer) = 0;
			//渲染结束后清空渲染列表			
			virtual void EndRender() = 0;

			virtual int GetRenderableCount() = 0;
			virtual RENDER_LIST &GetRenderList() = 0;
		};
	}
}

#endif