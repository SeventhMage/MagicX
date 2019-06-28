#include "CTableConfigManager.h"
#include "CTableConfig.h"
#include "mxDef.h"


namespace mx
{
	namespace resource
	{

		CTableConfigManager::CTableConfigManager()
		{

		}

		CTableConfigManager::~CTableConfigManager()
		{
			for (auto table : m_tabelConfig)
			{
				SAFE_DEL(table.second);
			}
		}

		IResource * CTableConfigManager::LoadResource(const char *filename)
		{
			if (m_tabelConfig.find(filename) == m_tabelConfig.end())
			{
				m_tabelConfig[filename] = new CTableConfig(filename);
			}
			return m_tabelConfig[filename];
		}

		void CTableConfigManager::UnLoadResource(IResource *pResource)
		{
			for (auto table : m_tabelConfig)
			{
				if (table.second == pResource)
				{
					m_tabelConfig.erase(table.first);
					break;
				}
			}
			SAFE_DEL(pResource);
		}

		const ITableConfig * CTableConfigManager::GetTableConfig(const char *filename) const
		{
			auto it = m_tabelConfig.find(filename);
			if (it != m_tabelConfig.end())
				return it->second;
			return nullptr;
		}

	}
}