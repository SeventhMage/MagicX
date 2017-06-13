/************************************************************************/
/* 每一组渲染队列包含了使用当前材质的渲染列表                           */
/************************************************************************/
#ifndef _RENDER_I_RENDER_QUEUE_H_
#define _RENDER_I_RENDER_QUEUE_H_

#include <vector>

namespace se
{
	namespace render
	{
		class IRenderQueue
		{
		public:
			virtual ~IRenderQueue(){}
		};

		typedef std::vector<IRenderQueue *> RenderQueueGroup;
	}
}

#endif