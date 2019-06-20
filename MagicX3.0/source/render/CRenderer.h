/************************************************************************/
/* 渲染器实现                                                           */
/************************************************************************/
#ifndef _MX_RENDER_C_RENDERER_H_
#define _MX_RENDER_C_RENDERER_H_

#include "render/IRenderer.h"
#include "render/IMaterialManager.h"
#include "screenalignedquad/CScreenAlignedQuadManager.h"

#include <vector>

namespace mx
{
	namespace render
	{
		class CRenderer : public IRenderer
		{
		public:
			CRenderer(IRenderDriver *pRenderDriver);
			virtual ~CRenderer();
			
			virtual void Initialize(int width, int height);

			virtual IRenderDriver *GetRenderDriver() { return m_pRenderDriver; }			
			virtual IRenderable *CreateRenderable(IRenderQueue *pQueue);
			virtual void DestroyRenderable(IRenderable *pRenderable);

			virtual void DestroyMaterial(IMaterial *pMaterial);

			virtual void EndRender();

			virtual IRenderPhaseManager *GetRenderPhaseManager() const { return m_pRenderPhaseMgr; }
			virtual void ProcessRenderPhase();

			virtual IMaterialManager *GetMaterialManager() const { return m_pMaterialMgr; }

			virtual IScreenAlignedQuadManager *GetScreenAlignedQuadManager() const { return m_pScreenAlignedQuadManager; }
			virtual void SubmitScreenAlignedQuad() const;
		protected:
			virtual void AddVertexArrayObject(IVertexArrayObject *pObject);
			virtual void RemoveVertexArrayObject(IVertexArrayObject *pObject);
		protected:
			IRenderDriver *m_pRenderDriver;								//渲染驱动			

			std::vector<IVertexArrayObject *> m_vecVertexArray;			//顶点数组
			
			IMaterialManager *m_pMaterialMgr;

			IRenderPhaseManager *m_pRenderPhaseMgr;

			CScreenAlignedQuadManager *m_pScreenAlignedQuadManager;

		};
	}
}

#endif