#include "render/renderobject/CTextureMapObject.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		CTextureMapObject::CTextureMapObject(IRenderer *pRenderer)
			:CRenderObject(pRenderer)
		{
			if (m_pShaderProgram)
			{
				m_pShaderProgram->Attach("shader/texturemap.vs", ST_VERTEX);
				m_pShaderProgram->Attach("shader/texturemap.ps", ST_FRAGMENT);
				m_pShaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_TEXTURE0);
				m_pShaderProgram->Link();
			}
		}

		CTextureMapObject::~CTextureMapObject()
		{

		}

		void CTextureMapObject::Create(IRenderable *pRenderable)
		{
			if (m_pShaderProgram)
			{
				pRenderable->SetShaderProgram(m_pShaderProgram);
			}
		}

	}
}