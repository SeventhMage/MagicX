#ifndef _SE_C_SOFT_RENDERER_H_
#define _SE_C_SOFT_RENDERER_H_

#include "render/IRenderer.h"
#include "CSoftRenderDriver.h"
#include "base/CSingleton.h"

namespace se
{
	namespace render
	{
		class CSoftRenderer : public IRenderer, public base::CSingleton<CSoftRenderer>
		{
		public:
			CSoftRenderer();
			virtual ~CSoftRenderer();

			virtual IRenderDriver *GetRenderDriver() { return m_pSoftRD; }	
			virtual IRenderQueue *CreateRenderQueue(const char *material);
			virtual void DestroyRenderQueue(IRenderQueue *pRenderQueue);

		private:
			CSoftRenderDriver *m_pSoftRD;
		};
	}
}

#endif