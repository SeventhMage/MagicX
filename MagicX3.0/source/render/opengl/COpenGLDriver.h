/************************************************************************/
/* OpenGLÇý¶¯ÊµÏÖ                                                       */
/************************************************************************/

#ifndef _MX_RENDER_C_OPENGL_DRIVER_H_
#define _MX_RENDER_C_OPENGL_DRIVER_H_

#include <vector>

#include "render/IRenderDriver.h"
#include "render/IRenderable.h"

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
			void InitDriverWin32(HDC hDc);
#endif		
			virtual void OnSize(int x, int y, int width, int height);
		};
	}
}

#endif