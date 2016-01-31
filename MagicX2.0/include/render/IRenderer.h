#ifndef _MX_RENDER_IRENDERER_H_
#define _MX_RENDER_IRENDERER_H_

#include "core/CVector3.h"
#include "resource/IMesh.h"
#include "resource/IImage.h"
#include "SColor.h"

namespace mx
{
	namespace render
	{
		class IRenderer
		{
		public:
			virtual ~IRenderer(){};
			virtual void DrawLine(const core::CVector3 &vFrom, const core::CVector3 &vTo, const SColor &color = SColor(1, 0, 0, 0)) = 0;
			virtual void DrawImage(const resource::IImage *image, uint uScreenX = 0, uint uScreenY = 0) = 0;
			virtual void DrawMesh(const resource::IMesh *pMesh) = 0;
			
			virtual void AddMesh(resource::IMesh *pMesh) = 0;
			virtual void DrawRenderList() = 0;
		};
	}
}

#endif