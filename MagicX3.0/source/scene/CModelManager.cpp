#include "CModelManager.h"
#include "CModel.h"

namespace mx
{
	namespace scene
	{


		CModelManager::CModelManager()
		{

		}

		CModelManager::~CModelManager()
		{
			Clear();
		}

		bool CModelManager::CreateModel(const char *filename)
		{
			IModel *pModel = new CModel();
			if (pModel->Load(filename))
			{
				m_listModel.push_back(pModel);
				return true;
			}
			else
			{
				delete pModel;
				return false;
			}
		}

		void CModelManager::DestroyMode(IModel *pModel)
		{
			auto it = std::find(m_listModel.begin(), m_listModel.end(), pModel);
			if (*it)
			{
				IModel *pModel = *it;
				m_listModel.erase(it);
				if (pModel)
					delete pModel;
			}
		}

		void CModelManager::Clear()
		{
			for (auto it = m_listModel.begin(); it != m_listModel.end(); ++it)
			{
				if (*it)
					delete (*it);
			}
			m_listModel.clear();
		}

	}
}