/************************************************************************/
/* Í¼Ïñ¹ÜÀíÆ÷                                                           */
/************************************************************************/

#ifndef _MX_RESOURCE_C_IMAGE_MANAGER_H_
#define _MX_RESOURCE_C_IMAGE_MANAGER_H_

#include "resource/IImageManager.h"

namespace mx
{
	namespace resource
	{
		class CImageManager : public IImageManager
		{
		public:
			CImageManager();
			virtual ~CImageManager();

			virtual IResource *LoadResource(const char *filename);
			virtual void UnLoadResource(IResource *pResource);
		};
	}
}

#endif