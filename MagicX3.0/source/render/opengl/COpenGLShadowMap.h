/************************************************************************/
/* OpenGL“ı”∞Ã˘Õº                                                       */
/************************************************************************/

#ifndef _MX_RENDER_C_OPENGL_SHADOW_MAP_H_
#define _MX_RENDER_C_OPENGL_SHADOW_MAP_H_

#include "render/IShadowMap.h"
#include "mxType.h"
#include "render/IShaderProgram.h"

namespace mx
{
	namespace render
	{
		class COpenGLShadowMap : public IShadowMap
		{
		public:
			COpenGLShadowMap();
			virtual ~COpenGLShadowMap();

			virtual void Render();
		private:
			uint m_hDepthTexture;
			uint m_hDepthFBO;
			IShaderProgram *pShaderProgram;
		};
	}
}

#endif