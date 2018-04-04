/************************************************************************/
/* 资源通过IResourceLoader实现真正加载，场景等地用的时候通过此接口调用，*/
/* 实现加载过程与使用的分离。                                           */
/************************************************************************/
#ifndef _I_RESOURCE_RESOURCE_H_
#define _I_RESOURCE_RESOURCE_H_

#include "IResourceLoader.h"

namespace se
{
	namespace resource
	{
		class IResource
		{
		public:
			virtual ~IResource(){}
			
		};
	}
}

#endif