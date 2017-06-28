#include "CMaterialManager.h"
#include "resource/IMaterialResource.h"
#include "CSoftEngine.h"
#include "CMaterial.h"
#include "base/StringHelper.h"

namespace se
{
	namespace render
	{

		CMaterialManager::CMaterialManager()
		{

		}

		CMaterialManager::~CMaterialManager()
		{
			for (auto it = m_mapMaterial.begin(); it != m_mapMaterial.end(); ++it)
			{
				IMaterial *pMaterial = it->second;			
				SAFE_DEL(pMaterial);
			}
		}

		int CMaterialManager::CreateMaterial(const char *filename)
		{
			resource::IMaterialResource *pMaterialResource = dynamic_cast<resource::IMaterialResource *>
				(CSoftEngine::GetResourceManager()->LoadResource(filename));
			if (pMaterialResource)
			{
				int materialId = m_mapMaterial.size() + 1;
				IMaterial *pMaterial = new CMaterial(materialId);
				std::string strColor = pMaterialResource->GetValue(resource::MRA_COLOR);
				StringArray colorArray = base::Split(strColor, ",");
				if (colorArray.size() >= 3)
				{
					pMaterial->SetColor(math::CVector3(atoi(colorArray[0].c_str()), atoi(colorArray[1].c_str()),
						atoi(colorArray[2].c_str())));
				}
				std::string strIllumination = pMaterialResource->GetValue(resource::MRA_ILLUMINATION);
				pMaterial->SetIllumination(strIllumination);
				m_mapMaterial[filename] = pMaterial;
			}
		}

		int CMaterialManager::GetMaterialID(const char *filename)
		{
			if (m_mapMaterial.find(filename) != m_mapMaterial.end())
			{
				return m_mapMaterial[filename]->GetID();
			}
			return NULL;
		}

		IMaterial * CMaterialManager::GetMaterial(int materialId)
		{
			return NULL;
		}

		void CMaterialManager::DestroyMaterial(const char *filename)
		{
			auto it = m_mapMaterial.find(filename);
			if (it != m_mapMaterial.end())
			{
				IMaterial *pMaterial = m_mapMaterial[filename];
				SAFE_DEL(pMaterial);
				m_mapMaterial.erase(it);
			}
		}

		void CMaterialManager::DestroyMaterial(int materialId)
		{

		}

	}
}