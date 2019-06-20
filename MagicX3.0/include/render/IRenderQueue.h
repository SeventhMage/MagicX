#ifndef _MX_RENDER_I_RENDER_QUEUE_H_
#define _MX_RENDER_I_RENDER_QUEUE_H_ 

#include "IRenderable.h"

#include <map>
#include <vector>

namespace mx
{
	namespace render
	{
		class IMaterial;
		class IRenderQueue
		{
		public:
			virtual void AddRenderable(IRenderable *) = 0;
			virtual void RemoveRenderable(IRenderable *) = 0;
			virtual void Clear() = 0;
			virtual void Render() = 0;
			virtual IMaterial *GetMaterial() const = 0;
			virtual void BindPhaseUniform() = 0;
			virtual void SetPhaseTexture(const char *name,int phaseid, int slot, int index) = 0;
		};
		typedef std::map<int, IRenderQueue *> RenderQueueGroup;	//k:materialid
		typedef std::vector<IRenderQueue *> RenderQueueArray;
	}
}

#endif