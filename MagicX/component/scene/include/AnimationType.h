#ifndef _MX_SCENE_ANIMATION_TYPE_H_
#define _MX_SCENE_ANIMATION_TYPE_H_

#include "../include/common/mxDef.h"

namespace mx
{
	namespace scene
	{
		enum EAnimationType
		{
			E_AT_STAND = 0,
			E_AT_WALK_FORWARD,
			E_AT_WALK_BACK,
			E_AT_WALK_LEFT,
			E_AT_WALK_RIGHT,
			E_AT_RUN_FORWARD,
			E_AT_RUN_LEFT,
			E_AT_RUN_RIGHT,
			E_AT_JUMP,
			E_AT_SWIM_FORWARD,
			E_AT_SWIM_BACK,
			E_AT_SWIM_LEFT,
			E_AT_SWIM_RIGHT,

			E_AT_NUM
		};

		typedef struct
		{
			EAnimationType animTypeId;
			CString sAnimName;
		}SAnimationType;

		SAnimationType g_animationTypes[] =
		{
			{ E_AT_STAND , "stand" },
			{ E_AT_WALK_FORWARD , "walkforward"},
		};
	}
}

#endif
