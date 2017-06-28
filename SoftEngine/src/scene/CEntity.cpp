#include "CEntity.h"
#include "CSoftEngine.h"
#include "resource/IModel.h"

namespace se
{
	namespace scene
	{
		CEntity::CEntity(const char *name, CSceneNode *pNode)
			:m_strEntityName(name)
			, m_pSceneNode(pNode)		
			, m_pRenderCell(nullptr)
		{
			 resource::IModel *pModel = dynamic_cast<resource::IModel *>(CSoftEngine::GetResourceManager()->LoadResource(name));
			 if (pModel)
			 {
				 int materialId = CSoftEngine::GetMaterialManager()->GetMaterialID(pModel->GetMaterial().c_str());

				 CSoftEngine::GetResourceManager()->ReleaseResource(pModel);
			 }
		}

		CEntity::~CEntity()
		{
			
		}

		void CEntity::Update(int delta)
		{
			//����οռ�ת�����ύ����Ⱦ����

		}

		bool CEntity::Culled(ICamera *pCamera)
		{
			return false;
		}

	}
}