#ifndef _MX_SCENE_C_SKELETAL_ANIMATION_H_
#define _MX_SCENE_C_SKELETAL_ANIMATION_H_

#include "IAnimation.h"

namespace mx
{
	namespace scene
	{
		class CSkeletalAnimation : public IAnimation
		{
		public:
			CSkeletalAnimation();
			virtual ~CSkeletalAnimation();
		};
	}
}

#endif
