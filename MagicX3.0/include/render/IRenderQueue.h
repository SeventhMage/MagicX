#ifndef _MX_RENDER_I_RENDER_QUEUE_H_
#define _MX_RENDER_I_RENDER_QUEUE_H_ 

#include "IRenderable.h"

#include <map>

namespace mx
{
	namespace render
	{
		class IMaterial;
		class IRenderQueue
		{
		public:
			virtual void AddRenderable(IRenderable *) = 0;
			virtual void Clear() = 0;
			virtual void Render() = 0;
			virtual IMaterial *GetMaterial() const = 0;
			virtual void AddPhaseQuote(int phaseId) = 0;
			virtual void BindPhaseUniform() = 0;
			virtual void SetPhaseTexture(const char *name, int slot, int flag) = 0;
		};
		typedef std::map<int, IRenderQueue *> RenderQueueGroup;	//k:materialid
	}
}

#endif