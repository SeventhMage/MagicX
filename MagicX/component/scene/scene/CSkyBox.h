#ifndef _C_SKY_BOX_H_
#define _C_SKY_BOX_H_

#include "../include/ISkyBoxSceneNode.h"
#include "common/mxDef.h"
#include "IRenderer.h"
#include "ITexture.h"
#include "IGPUBuffer.h"

namespace mx
{
	namespace scene
	{
		class CSkyBox : public ISkyBoxSceneNode
		{
		public:
			CSkyBox(render::IRenderer *renderer);
			virtual ~CSkyBox();

			virtual bool Create(const char *filename);
			virtual bool Create(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom);
			virtual void UpdateViewProjectMatrix(const CMatrix4 &viewMat4);

			virtual void UpdateImp(int elapsedTime);
			virtual void RenderImp();
		private:
			CString m_filename;
			render::IRenderer *m_pRenderer;
			render::ITexture *m_pTexture;
			render::IGPUBuffer *m_pGPUBuffer;
			render::IRenderableObject *m_pRenderableObject;
			float *m_pBoxData;
			CMatrix4 m_viewMat4;
		};
	}
}

#endif