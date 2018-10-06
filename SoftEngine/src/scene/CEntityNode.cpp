#include "CEntityNode.h"

namespace se
{
	namespace scene
	{


		CEntityNode::CEntityNode(const char *entityName, IScene *pScene)
			:CSceneNode(pScene), m_pEntity(new CEntity(entityName, this))
		{

		}

		CEntityNode::~CEntityNode()
		{
			SAFE_DEL(m_pEntity);
		}

		void CEntityNode::Update(int delta)
		{
			CSceneNode::Update(delta);

			if (m_pEntity)
			{
				m_pEntity->Update(delta);
			}
		}

	}
}