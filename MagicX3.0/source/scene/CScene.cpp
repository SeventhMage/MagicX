#include "CScene.h"
#include "scene/CSceneNode.h"
#include "mx.h"

namespace mx
{
	namespace scene
	{


		CScene::CScene()
		{
			m_pRootNode = new CSceneNode();
		}

		CScene::~CScene()
		{
			if (m_pRootNode)
				delete m_pRootNode;
		}

		void CScene::Draw()
		{
			if (m_pRootNode)
				m_pRootNode->Render();
		}

		void CScene::Update(int delta)
		{
			if (m_pRootNode)
				m_pRootNode->Update(delta);
		}

	}
}