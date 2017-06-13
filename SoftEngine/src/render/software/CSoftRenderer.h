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
		private:
			CSoftRenderDriver *m_pSoftRD;
		};
	}
}

#endif