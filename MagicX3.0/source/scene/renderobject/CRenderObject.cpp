#include "scene/renderobject/CRenderObject.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{

		CRenderObject::CRenderObject()
		{
			m_pVAO = RENDERER->CreateVertexArrayObject();
		}

		CRenderObject::~CRenderObject()
		{
			RENDERER->DestroyVertexArrayObject(m_pVAO);
		}

		void CRenderObject::Update(IRenderable *pRenderable, const UniformMap &param)
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
			}
		}

	}
}