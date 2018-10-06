#ifndef _SE_I_ENTITY_H_
#define _SE_I_ENTITY_H_

#include "ICamera.h"

namespace se
{
	namespace scene
	{
		class IEntity
		{
		public:
			virtual ~IEntity(){}

			virtual void Update(int delta) = 0;
		};
	}
}

#endif
