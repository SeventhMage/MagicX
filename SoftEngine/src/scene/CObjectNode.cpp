#include "CObjectNode.h"

namespace se
{
	namespace scene
	{		
		CObjectNode::CObjectNode(IScene *pScene, uint objID)
			:CSceneNode(pScene), m_ObjectID(objID)
		{
		}

		CObjectNode::~CObjectNode()
		{

		}

		void CObjectNode::Update(int delta)
		{
			CSceneNode::Update(delta);

		}

	}
}