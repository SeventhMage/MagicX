#include "CMaterialManager.h"
#include "resource/IMaterialResource.h"
#include "CSoftEngine.h"
#include "CMaterial.h"
#include "base/StringHelper.h"
#include "render/SColor.h"

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

		IMaterial *CMaterialManager::CreateMaterial(const char *filename)
		{
			resource::IMaterialResource *pMaterialResource = dynamic_cast<resource::IMaterialResource *>
				(CSoftEngine::GetResourceManager()->LoadResource(filename));
			if (pMaterialResource)
			{
				int materialId = m_mapMaterial.size() + 1;
				IMaterial *pMaterial = new CMaterial(materialId, filename);
				std::string strColor = pMaterialResource->GetValue(resource::MRA_COLOR);
				StringArray colorArray = base::Split(strColor, ",");
				if (colorArray.size() >= 3)
				{
					pMaterial->SetColor(render::Color(1.0f, (float)atof(colorArray[0].c_str()), (float)atof(colorArray[1].c_str()),
						(float)atof(colorArray[2].c_str())));
				}
				std::string strIllumination = pMaterialResource->GetValue(resource::MRA_ILLUMINATION);
				pMaterial->SetIllumination(strIllumination);

				float ambientCoe = (float)atof(pMaterialResource->GetValue(resource::MRA_AMBIENT_COE).c_str());
				float diffuseCoe = (float)atof(pMaterialResource->GetValue(resource::MRA_DIFFUSE_COE).c_str());
				float specularCoe = (float)atof(pMaterialResource->GetValue(resource::MRA_SPECULAR_COE).c_str());
				int specularityCoe = atoi(pMaterialResource->GetValue(resource::MRA_SPECULARITY_COE).c_str());

				pMaterial->SetAmbientCoefficient(ambientCoe);
				pMaterial->SetDiffuseCoefficient(diffuseCoe);
				pMaterial->SetSpecularCoefficient(specularCoe);
				pMaterial->SetSpecularityCoefficient(specularityCoe);

				m_mapMaterial[materialId] = pMaterial;
				CSoftEngine::GetResourceManager()->ReleaseResource(pMaterialResource);
				return pMaterial;
			}
			return nullptr;
		}

		int CMaterialManager::GetMaterialID(const char *filename)
		{
			for (auto it = m_mapMaterial.begin(); it != m_mapMaterial.end(); ++it)
			{
				IMaterial *pMaterial = it->second;
				if (pMaterial)
				{
					if (pMaterial->GetName() == filename)
					{
						return pMaterial->GetID();
					}
				}
			}
			return 0;
		}

		void CMaterialManager::DestroyMaterial(IMaterial *pMaterial)
		{
			auto it = m_mapMaterial.find(pMaterial->GetID());
			if (it != m_mapMaterial.end())
			{
				IMaterial *pTemp = it->second;
				SAFE_DEL(pTemp);
				m_mapMaterial.erase(it);
			}
		}

	}
}