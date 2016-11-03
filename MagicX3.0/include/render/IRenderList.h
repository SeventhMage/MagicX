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
			
			//清空渲染列表等初始工作			
			virtual void BeginRender() = 0;
			//执行渲染
			virtual void Render() = 0;
			virtual int GetRenderableCount() = 0;
			virtual RENDER_LIST &GetRenderList() = 0;
		};
	}
}

#endif