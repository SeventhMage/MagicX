#ifndef _C_SKY_BOX_H_
#define _C_SKY_BOX_H_

#include <string>

#include "scene/ISkyBox.h"
#include "mxType.h"
#include "render/IRenderer.h"
#include "render/ITexture.h"
#include "render/IGPUBuffer.h"
#include "core/CMatrix4.h"

namespace mx
{
	namespace scene
	{
		class CSkyBox : public ISkyBox
		{
		public:
			CSkyBox(render::IRenderer *renderer, float radius);
			virtual ~CSkyBox();

			virtual bool Create(const char *filename);
			virtual bool Create(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom);

			virtual void Update(int elapsedTime, const core::CMatrix4 &mat4MVP);
			virtual void RenderImp();
		private:
			std::string m_filename;
			render::IRenderer *m_pRenderer;
			render::ITexture *m_pTexture;
			render::IGPUBuffer *m_pGPUBuffer;
			render::IRenderableObject *m_pRenderableObject;
			float *m_pBoxData;
			core::CMatrix4 m_viewMat4;
			float m_fRadius;
		};
	}
}

#endif