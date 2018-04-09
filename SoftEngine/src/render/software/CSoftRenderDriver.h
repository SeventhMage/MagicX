#ifndef _SE_C_SOFT_RENDER_DRIVER_H_
#define _SE_C_SOFT_RENDER_DRIVER_H_

#include "render/IRenderDriver.h"
#include "render/SRenderMemory.h"

namespace se
{
	namespace render
	{
		class CSoftRenderDriver : public IRenderDriver
		{
		public:		
			CSoftRenderDriver();
			virtual ~CSoftRenderDriver();

			virtual void InitDriver(const SRenderContext &context);
			virtual void OnSize(int x, int y, int width, int height);
			virtual RenderDriverType GetDriverType(){ return RDT_SOFTWARE; }			

		public:
			uint *GetDrawBuffer(){ return m_pDrawBuffer; }
			float *GetDepthBuffer(){ return m_pDepthBuffer; }
			inline uint GetBufferWidth(){ return m_uBufferWidth; }
			inline uint GetBufferHeight(){ return m_uBufferHeight; }
			void DrawBuffer();			
			void Clear();
		private:
			void CreateBuffer();
		private:
			uint *m_pDrawBuffer;
			float *m_pDepthBuffer;
			uint m_uBufferWidth;
			uint m_uBufferHeight;
		};
	}
}

#endif