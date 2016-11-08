/************************************************************************/
/* 资源管理器接口                                                       */
/************************************************************************/

#ifndef _MX_RESOURCE_I_RESOURCE_MANAGER_H_
#define _MX_RESOURCE_I_RESOURCE_MANAGER_H_

#include "IResource.h"

namespace mx
{
	namespace resource
	{
		class IResourceManager
		{
		public:			
			virtual ~IResourceManager(){};

			//从文件中载入资源
			virtual IResource *LoadResource(const char *filename) = 0;	
			//内存中卸载资源
			virtual void UnLoadResource(IResource *pResource) = 0;
		};
	}
}

#endif