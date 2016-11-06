#include "CEntityManager.h"

namespace mx
{
	namespace scene
	{

		CEntityManager::CEntityManager()
		{

		}

		CEntityManager::~CEntityManager()
		{

		}

		IEntity * CEntityManager::CreateEntity(IVertex *pVertex)
		{

		}

		IEntity * CEntityManager::CreateEntity(IVertex *pVertex, const char *texname)
		{
			if (pVertex && texname)
			{
				uint vertAttr = pVertex->GetVertexAttribute();
				
				
			}
		}

	}
}