#ifndef _RESOURCE_I_SCENE_RESOURCE_H_
#define _RESOURCE_I_SCENE_RESOURCE_H_

#include "IResource.h"
#include "math/CVector3.h"
#include <vector>

namespace se
{
	namespace resource
	{
		struct SCameraParam
		{
			math::CVector3 position;
			math::CVector3 direction;
			math::CVector3 up;
			float fov;
			float nearClip;
			float farClip;
		};

		struct SEntityInfo
		{
			char name[256];
			math::CVector3 position;
		};

		class ISceneResource : public IResource
		{
		public:
			virtual ~ISceneResource(){}
			
			virtual SCameraParam GetCameraParam() = 0;
			virtual int GetEntityCount() = 0;
			virtual SEntityInfo GetEntityInfoByIdx(int idx) = 0;
		};
	}
}

#endif