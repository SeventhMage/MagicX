#include "render/renderobject/CRenderObject.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		CRenderObject::CRenderObject(IRenderer *pRenderer)
			:m_pRenderer(pRenderer)
			, m_pShaderProgram(nullptr)
		{
			m_pVAO = pRenderer->CreateVertexArrayObject();
			m_pShaderProgram = RENDERER->CreateShaderProgram();
		}

		CRenderObject::~CRenderObject()
		{
			m_pRenderer->DestroyVertexArrayObject(m_pVAO);
			SAFE_DEL(m_pShaderProgram);
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

				//IShaderProgram *pShadowShaderProgram = pRenderable->GetShadowShaderProgram();
				//if (pShadowShaderProgram && shadowParam)
				//{
				//	for (auto it = shadowParam->begin(); it != shadowParam->end(); ++it)
				//	{
				//		pShadowShaderProgram->SetUniform(it->first, it->second);
				//	}
				//}
			}
		}

	}
}