#include "render/renderobject/CReflectObject.h"
#include "mx.h"

namespace mx
{
	namespace render
	{

		CReflectObject::CReflectObject(IRenderer *pRenderer)
			:CRenderObject(pRenderer)
		{
			if (m_pShaderProgram)
			{
				m_pShaderProgram->Attach("shader/reflection.vs", ST_VERTEX);
				m_pShaderProgram->Attach("shader/reflection.ps", ST_FRAGMENT);
				m_pShaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_NORMAL);
				m_pShaderProgram->Link();

				int cubeUnit = 0;
				m_pShaderProgram->SetUniform("cubeMap", &cubeUnit);
			}
		}

		CReflectObject::~CReflectObject()
		{
		
		}


		void CReflectObject::Create(IRenderable *pRenderable)
		{
			if (!m_pVAO || !pRenderable) return;

			if (m_pShaderProgram)
			{
				pRenderable->SetShaderProgram(m_pShaderProgram);
			}
		}

		void CReflectObject::SetTexture(IRenderable *pRenderable)
		{
			if (!pRenderable) return;

			IScene *pScene = SCENEMGR->GetCurrentScene();
			if (pScene)
			{
				ISkyBox *pSkyBox = pScene->GetSkyBox();
				if (pSkyBox)
				{
					pRenderable->SetTexture(0, pSkyBox->GetTexture());
				}
			}
		}

	}
}