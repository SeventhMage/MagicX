#ifndef _MX_RENDER_OPENGLRENDERER_H_
#define _MX_RENDER_OPENGLRENDERER_H_

#include "render/IRenderer.h"

namespace mx
{
	namespace render
	{
		class COpenGLRenderer : public IRenderer
		{
		public:
			COpenGLRenderer();
			virtual ~COpenGLRenderer();
			virtual void DrawLine(const core::CVector3 &vFrom, const core::CVector3 &vTo, const SColor &color = SColor(1, 0, 0, 0));
			virtual void DrawImage(const resource::IImage *image, uint uScreenX = 0, uint uScreenY = 0);
			virtual void DrawMesh(const resource::IMesh *pMesh);

			virtual void AddMesh(resource::IMesh *pMesh);
			virtual void DrawRenderList();
		};
	}
}

#endif