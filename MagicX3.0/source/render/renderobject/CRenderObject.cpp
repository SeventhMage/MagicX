#include "render/renderobject/CRenderObject.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		CRenderObject::CRenderObject()
		{
			m_pVAO = RENDERER->CreateVertexArrayObject();
		}

		CRenderObject::~CRenderObject()
		{
			RENDERER->DestroyVertexArrayObject(m_pVAO);
		}

		void CRenderObject::Update(IRenderable *pRenderable, const UniformMap &param, const UniformMap *shadowParam)
		{
			if (pRenderable)
			{
				IShaderProgram *pShaderProgram = pRenderable->GetShaderProgram();
				if (pShaderProgram)
				{
					for (auto it = param.begin(); it != param.end(); ++it)
					{
						pShaderProgram->SetUniform(it->first, it->second);
					}
				}

				IShaderProgram *pShadowShaderProgram = pRenderable->GetShadowShaderProgram();
				if (pShadowShaderProgram && shadowParam)
				{
					for (auto it = shadowParam->begin(); it != shadowParam->end(); ++it)
					{
						pShadowShaderProgram->SetUniform(it->first, it->second);
					}
				}
			}
		}

	}
}