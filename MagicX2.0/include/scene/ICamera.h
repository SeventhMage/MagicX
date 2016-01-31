#ifndef _MX_SCENE_ICAMERA_H_
#define _MX_SCENE_ICAMERA_H_

#include "core/CMatrix4.h"

namespace mx
{
	namespace scene
	{
#define CAM_MODEL_ELUER 1
#define CAM_MODEL_UVN	2
		using namespace core;
		class ICamera
		{
		public:
			ICamera(){}
			virtual ~ICamera(){}
			virtual void BuildViewMatrix() = 0;
			virtual void BuildProjMatrix() = 0;
			virtual const CMatrix4 &GetViewMatrix() = 0;
			virtual const CMatrix4 &GetProjMatrix() = 0;
			virtual const CMatrix4 &GetVPMatrix() = 0;
		};
	}
}

#endif