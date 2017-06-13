/************************************************************************/
/* ÿһ����Ⱦ���а�����ʹ�õ�ǰ���ʵ���Ⱦ�б�                           */
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