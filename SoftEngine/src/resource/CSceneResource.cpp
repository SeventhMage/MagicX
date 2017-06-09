#include "CSceneResource.h"

namespace se
{
	namespace resource
	{

		CSceneResource::CSceneResource(const char *filename)
		{
			m_pSceneLoader = new CSceneLoader(filename);
		}

		CSceneResource::~CSceneResource()
		{
			SAFE_DEL(m_pSceneLoader);
		}

		SCameraParam CSceneResource::GetCameraParam()
		{
			SCameraParam camParam = {m_pSceneLoader->GetCameraPosition(), m_pSceneLoader->GetCameraDirection(), m_pSceneLoader->GetCameraUp(),
				m_pSceneLoader->GetCameraFov(), m_pSceneLoader->GetCameraNearClip(), m_pSceneLoader->GetCameraFarClip()
				};
			return camParam;
		}

		int CSceneResource::GetEntityCount()
		{
			return m_pSceneLoader->GetEntityCount();
		}

		SEntityInfo CSceneResource::GetEntityInfoByIdx(int idx)
		{
			const std::vector<SEntityInfo> entityInfo = m_pSceneLoader->GetEntityInfo();
			if (idx >= 0 && idx < entityInfo.size())
			{
				return entityInfo[idx];
			}
			SEntityInfo si = {"", math::CVector3(0, 0, 0)};
			return si;
		}

	}
}