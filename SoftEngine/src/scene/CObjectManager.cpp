#include "CObjectManager.h"
#include "CSphereObject.h"
#include "base/seDef.h"

namespace se
{
	namespace scene
	{


		CObjectManager::CObjectManager()
		{

		}

		CObjectManager::~CObjectManager()
		{
			for (auto it = m_mapObjects.begin(); it != m_mapObjects.end(); ++it)
			{
				SAFE_DEL(it->second);
			}
			m_mapObjects.clear();
		}

		uint CObjectManager::CreateSphere(float fRadius, const render::Color &color)
		{
			size_t size = m_mapObjects.size();
			uint id = size + 1;
			m_mapObjects[id] = new CSphereObject(id, fRadius, color);
			return id;
		}

	}
}