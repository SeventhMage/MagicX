#ifndef _SCENE_I_OBJECT_MANAGER_H_
#define _SCENE_I_OBJECT_MANAGER_H_

#include "IObject.h"
#include "base/seType.h"

namespace se
{
	namespace scene
	{
		class IObjectManager
		{
		public:
			virtual ~IObjectManager(){}

			virtual uint CreateSphere(float fRadius, const render::Color &color) = 0;
		};
	}
}

#endif