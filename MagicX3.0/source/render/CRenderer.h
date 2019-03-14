/************************************************************************/
/* ��Ⱦ��ʵ��                                                           */
/************************************************************************/
#ifndef _MX_RENDER_C_RENDERER_H_
#define _MX_RENDER_C_RENDERER_H_

#include "render/IRenderer.h"
#include "render/IMaterialManager.h"

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
			virtual IRenderable *CreateRenderable(IRenderList *pRenderList);
			virtual IRenderable *CreateRenderable(IRenderQueue *pQueue);
			virtual void DestroyRenderable(IRenderable *pRenderable);

			virtual void DestroyMaterial(IMaterial *pMaterial);

			virtual void Render();
			virtual void EndRender();

			virtual IRenderPhaseManager *GetRenderPhaseManager() const { return m_pRenderPhaseMgr; }
			virtual void ProcessRenderPhase() const;

			virtual IMaterialManager *GetMaterialManager() const { return m_pMaterialMgr; }


		protected:
			virtual void AddVertexArrayObject(IVertexArrayObject *pObject);
			virtual void RemoveVertexArrayObject(IVertexArrayObject *pObject);
		protected:
			IRenderDriver *m_pRenderDriver;								//��Ⱦ����			

			std::vector<IVertexArrayObject *> m_vecVertexArray;			//��������
			
			IMaterialManager *m_pMaterialMgr;

			IRenderPhaseManager *m_pRenderPhaseMgr;

		};
	}
}

#endif