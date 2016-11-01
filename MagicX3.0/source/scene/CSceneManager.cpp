#include "CSceneManager.h"

namespace mx
{
	namespace scene
	{

		CSceneManager::CSceneManager()
			:m_pCurrentScene(NULL)
		{

		}

		CSceneManager::~CSceneManager()
		{

		}


		void CSceneManager::Update(int delta)
		{
			if (m_pCurrentScene)
			{
				ISceneNode *pRootNode = m_pCurrentScene->GetRootNode();
				if (pRootNode)
				{
					pRootNode->Update(delta);
				}
			}
		}

		IScene * CSceneManager::LoadScene(const char *filename)
		{
			return nullptr;
		}

		void CSceneManager::Draw(render::IRenderer *pRenderer)
		{
			if (pRenderer && m_pCurrentScene)
			{
				ISceneNode *pRootNode = m_pCurrentScene->GetRootNode();
				if (pRootNode)
				{
					pRootNode->Submit();
				}
				pRenderer->Render();
			}
		}

	}
}