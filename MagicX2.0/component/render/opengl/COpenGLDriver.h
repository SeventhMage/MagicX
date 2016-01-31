#ifndef _MX_RENDER_OPENGLDRIVER_H_
#define _MX_RENDER_OPENGLDRIVER_H_

#include "render/IRenderDriver.h"
#include "mxType.h"
#include "COpenGLRenderer.h"
#ifdef WIN32
#include <windows.h>
#endif

namespace mx
{
	namespace render
	{
		class COpenGLDriver : public IRenderDriver
		{
		public:
			COpenGLDriver();
			virtual ~COpenGLDriver();
#ifdef WIN32
			virtual bool SetupWin32Driver(HDC hDC);
#endif
			virtual void OnSize(uint uPosX, uint uPosY, uint uWidth, uint uHeight);
			virtual IRenderer *GetRenderer() { return m_pRenderer; }
		private:
			COpenGLRenderer *m_pRenderer;
		};
	}
}

#endif