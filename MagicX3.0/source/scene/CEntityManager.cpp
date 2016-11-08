#include "CEntityManager.h"
#include "scene/CUnit.h"

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

		CEntity * CEntityManager::CreateEntity(IVertex *pVertex, const char *texname)
		{
			if (pVertex && texname)
			{
				uint vertAttr = pVertex->GetVertexAttribute();
				CUnit *pUnit = new CUnit(pVertex, texname);
				return pUnit;
			}
			return nullptr;
		}

	}
}