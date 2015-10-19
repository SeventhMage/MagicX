#ifndef _C_SKY_BOX_H_
#define _C_SKY_BOX_H_

#include "../include/ISkyBox.h"

namespace mx
{
	namespace scene
	{
		class CSkyBox : public ISkyBox
		{
		public:
			CSkyBox();
			virtual ~CSkyBox();

			virtual bool Create();
			virtual void Update();
		};
	}
}

#endif