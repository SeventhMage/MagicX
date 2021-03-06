#include "render\IVertexArrayObject.h"
/************************************************************************/
/* ��Ⱦ����                                                             */
/************************************************************************/

#ifndef _MX_RENDER_C_RENDER_OBJECT_H_
#define _MX_RENDER_C_RENDER_OBJECT_H_

#include "render/renderobject/IRenderObject.h"
#include "render/IRenderable.h"
#include "render/IRenderer.h"

namespace mx
{
	namespace render
	{
		using namespace render;
		class CRenderObject : public IRenderObject
		{
		public:
			CRenderObject(IRenderer *pRenderer);
			virtual ~CRenderObject();

			virtual void SetTexture(IRenderable *pRenderable){}
			virtual render::IVertexArrayObject *GetVAO() { return m_pVAO; }
			virtual void Update(IRenderable *pRenderable, const UniformMap &normalParam, const UniformMap *shadowParam = nullptr);
			
		protected:
			IVertexArrayObject *m_pVAO;
			IShaderProgram *m_pShaderProgram;
			IRenderer *m_pRenderer;
		};
	}
}

#endif