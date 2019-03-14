#ifndef _MX_RENDER_I_RENDER_QUEUE_H_
#define _MX_RENDER_I_RENDER_QUEUE_H_ 

#include "IRenderable.h"

#include <map>

namespace mx
{
	namespace render
	{
		class IRenderQueue
		{
		public:
			virtual void AddRenderable(IRenderable *) = 0;
			virtual void Clear() = 0;
			virtual void Render() = 0;
		};
		typedef std::map<int, IRenderQueue *> RenderQueueGroup;	//k:materialid
	}
}

#endif