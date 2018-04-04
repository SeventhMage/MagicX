#ifndef _RESOURCE_C_SCENE_RESOURCE_H_
#define _RESOURCE_C_SCENE_RESOURCE_H_

#include "resource/ISceneResource.h"
#include "CSceneLoader.h"

namespace se
{
	namespace resource
	{
		class CSceneResource : public ISceneResource
		{
		public:
			CSceneResource(const char *filename);
			virtual ~CSceneResource();
									
			virtual SCameraParam GetCameraParam();
			virtual int GetEntityCount();
			virtual SEntityInfo GetEntityInfoByIdx(uint idx);
		private:
			CSceneLoader *m_pSceneLoader;
		};
	}
}

#endif