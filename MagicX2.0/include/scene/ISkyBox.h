#ifndef _MX_SCENE_ISKYBOX_H_
#define _MX_SCENE_ISKYBOX_H_

#include "mxType.h"
#include "core/CMatrix4.h"

namespace mx
{
	namespace scene
	{
		class ISkyBox
		{
		public:
			ISkyBox(){}
			virtual ~ISkyBox(){}

			virtual void Update(int elapsedTime, const core::CMatrix4 &mat4MVP) = 0;
			virtual bool Create(const char *filename) = 0;
			virtual bool Create(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom)  = 0;
		};
	}
}

#endif // !_I_SKY_BOX_INC_
