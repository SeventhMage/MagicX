/************************************************************************/
/* ��Դ�������ӿ�                                                       */
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

			//���ļ���������Դ
			virtual IResource *LoadResource(const char *filename) = 0;	
			//�ڴ���ж����Դ
			virtual void UnLoadResource(IResource *pResource) = 0;
		};
	}
}

#endif