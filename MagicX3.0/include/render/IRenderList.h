/************************************************************************/
/* 渲染列表接口                                                         */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDER_QUEUE_H_
#define _MX_RENDER_I_RENDER_QUEUE_H_

#include "IRenderable.h"

namespace mx
{
	namespace render
	{

		class IRenderList
		{
		public:			
			virtual ~IRenderList(){}
			
			//添加渲染实体到渲染列表
			virtual void AddRenderable(IRenderable *pRenderable) = 0;
			//移除渲染实体
			virtual void RemoveRenderable(IRenderable *pRenderable) = 0;
			
			virtual void Clear() = 0;

			//执行渲染
			virtual void Render() = 0;

		};
	}
}

#endif