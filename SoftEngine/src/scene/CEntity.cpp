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
			, m_materialId(0)
		{
			 m_pModel = dynamic_cast<resource::IModel *>(CSoftEngine::GetResourceManager()->LoadResource(name));
		}

		CEntity::~CEntity()
		{
			CSoftEngine::GetResourceManager()->ReleaseResource(m_pModel);
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