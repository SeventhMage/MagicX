#include "scene/renderobject/CReflectObject.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{

		CReflectObject::CReflectObject()
		{
			
		}

		CReflectObject::~CReflectObject()
		{
		
		}


		void CReflectObject::Create(IRenderable *pRenderable)
		{
			if (!m_pVAO || !pRenderable) return;

			IShaderProgram *pShaderProgram = pRenderable->GetShaderProgram();
			if (pShaderProgram)
			{
				pShaderProgram->Attach("shader/reflection.vs", ST_VERTEX);
				pShaderProgram->Attach("shader/reflection.ps", ST_FRAGMENT);
				pShaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_NORMAL);
				pShaderProgram->Link();

				int cubeUnit = 0;
				pShaderProgram->SetUniform("cubeMap", &cubeUnit);
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