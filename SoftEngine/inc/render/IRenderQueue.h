/************************************************************************/
/* ÿһ����Ⱦ���а�����ʹ�õ�ǰ���ʵ���Ⱦ�б�                           */
/************************************************************************/
#ifndef _RENDER_I_RENDER_QUEUE_H_
#define _RENDER_I_RENDER_QUEUE_H_

#include "IRenderCell.h"

#include <map>

namespace se
{
	namespace render
	{
		class IRenderQueue
		{
		public:
			virtual ~IRenderQueue(){}
			virtual int GetMaterialID() = 0;
			virtual void AddRenderCell(IRenderCell *pCell) = 0;
			virtual void Clear() = 0;
			virtual void Render() = 0;
		};

		typedef std::map<int, IRenderQueue *> RenderQueueGroup;
	}
}

#endif