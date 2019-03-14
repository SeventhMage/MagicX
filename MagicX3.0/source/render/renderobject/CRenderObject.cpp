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

				for (auto it = param.begin(); it != param.end(); ++it)
				{
					pRenderable->SetUniform(it->first, it->second);
				}
			}
		}

	}
}