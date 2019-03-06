#include "render/renderobject/CTextureMapObject.h"
#include "mx.h"

namespace mx
{
	namespace render
	{
		CTextureMapObject::CTextureMapObject(IRenderer *pRenderer)
			:CRenderObject(pRenderer)
		{
		}

		CTextureMapObject::~CTextureMapObject()
		{

		}

		void CTextureMapObject::Create(IRenderable *pRenderable)
		{
			IShaderProgram *pShaderProgram = pRenderable->GetShaderProgram();
			if (pShaderProgram)
			{
				pShaderProgram->Attach("shader/texturemap.vs", ST_VERTEX);
				pShaderProgram->Attach("shader/texturemap.ps", ST_FRAGMENT);
				pShaderProgram->BindAttributeLocation(2, VAL_POSITION, VAL_TEXTURE0);
				pShaderProgram->Link();
			}
		}

	}
}