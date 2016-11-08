/************************************************************************/
/* 图像管理器接口                                                       */
/************************************************************************/

#ifndef _MX_RESOURCE_I_IMAGE_MANAGER_H_
#define _MX_RESOURCE_I_IMAGE_MANAGER_H_

#include "IResourceManager.h"

namespace mx
{
	namespace resource
	{
		class IImageManager : public IResourceManager
		{
		public:
			virtual ~IImageManager(){}			

		};
	}
}

#endif