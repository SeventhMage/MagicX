#ifndef _H_MESH_H_INC_
#define _H_MESH_H_INC_

#include "IResource.h"

namespace mx
{
	namespace scene
	{
		class IMesh : public resource::IResource
		{
		public:
			IMesh(){}
			virtual ~IMesh(){}
		};
	}
}

#endif