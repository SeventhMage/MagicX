#ifndef _I_SKY_BOX_INC_
#define _I_SKY_BOX_INC_

#include "common/mxDef.h"

namespace mx
{
	namespace scene
	{
		class ISkyBox
		{
		public:
			ISkyBox(){}
			virtual ~ISkyBox(){}
			
			virtual bool Create(const char *filename) = 0;
			virtual bool Create(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom)  = 0;
			virtual void Update(const CMatrix4 &viewMat4, int  elapsedTime) = 0;
		};
	}
}

#endif // !_I_SKY_BOX_INC_
