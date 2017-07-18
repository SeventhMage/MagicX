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
#ifdef WIN32
			virtual void InitDriverWin32(HDC hDc, int width, int height);
#endif
			virtual void OnSize(int x, int y, int width, int height);
			virtual RenderDriverType GetDriverType(){ return RDT_SOFTWARE; }			

		public:
			uint *GetDrawBuffer(){ return m_pDrawBuffer; }
			float *GetDepthBuffer(){ return m_pDepthBuffer; }
			uint GetBufferWidth(){ return m_uBufferWidth; }
			uint GetBufferHeight(){ return m_uBufferHeight; }
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