/************************************************************************/
/* 每个renderable存储了对渲染器的一次提交                               */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERABLE_H_
#define _MX_RENDER_I_RENDERABLE_H_

#include "IBufferObject.h"

namespace mx
{
	namespace render
	{
		class IRenderable
		{
		public:
			virtual ~IRenderable(){}
		
			virtual IBufferObject *GetVertexBufferObject() = 0;
			virtual IBufferObject *GetIndexBufferObject() = 0;

			//活跃的才能被渲染
			virtual void SetActive(bool bActive) = 0;
			virtual bool IsActive() = 0;

			//提交数据到渲染队列
			virtual void SumbitToRenderQueue() = 0;
			//绑定当前数据, 使渲染程序知道正在处理的是谁
			virtual void Bind() = 0;
		};
	}
}

#endif