/************************************************************************/
/* ��Ⱦ��ʵ��                                                           */
/************************************************************************/
#ifndef _MX_RENDER_C_RENDERER_H_
#define _MX_RENDER_C_RENDERER_H_

#include "render/IRenderer.h"

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
			
			virtual IRenderDriver *GetRenderDriver() { return m_pRenderDriver; }			
			virtual IRenderable *CreateRenderable(IRenderList *pRenderList);
			virtual void DestroyRenderable(IRenderable *pRenderable);

			virtual IMaterial *CreateMaterial();
			virtual void DestroyMaterial(IMaterial *pMaterial);

			virtual void Render();
			virtual void EndRender();


			virtual void SetRenderShadowMap(bool rend) { m_bRendShadow = rend; }
			virtual bool IsRenderShadowMap() { return m_bRendShadow; }
		protected:
			virtual void AddVertexArrayObject(IVertexArrayObject *pObject);
			virtual void RemoveVertexArrayObject(IVertexArrayObject *pObject);
		protected:
			IRenderDriver *m_pRenderDriver;								//��Ⱦ����			

			std::vector<IVertexArrayObject *> m_vecVertexArray;			//��������

			bool m_bRendShadow;											//��ǰ��ȾΪ��Ӱͼ
		};
	}
}

#endif