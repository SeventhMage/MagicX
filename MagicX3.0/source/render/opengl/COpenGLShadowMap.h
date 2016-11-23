/************************************************************************/
/* OpenGL“ı”∞Ã˘Õº                                                       */
/************************************************************************/

#ifndef _MX_RENDER_C_OPENGL_SHADOW_MAP_H_
#define _MX_RENDER_C_OPENGL_SHADOW_MAP_H_

#include "render/IShadowMap.h"
#include "mxType.h"
#include "render/IShaderProgram.h"
#include "scene/ICamera.h"

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
			virtual ITexture *GetShadowMap() { return m_pTexture; }
			virtual IShaderProgram *GetShaderProgram() { return m_pShaderProgram; }
		private:
			uint m_hDepthTexture;
			ITexture *m_pTexture;
			uint m_hDepthFBO;
			uint m_hDepthRBO;
			IShaderProgram *m_pShaderProgram;
			scene::ICamera *m_pShadowCamera;
		};
	}
}

#endif