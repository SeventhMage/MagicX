/************************************************************************/
/* 纹理资源接口                                                         */
/************************************************************************/

#ifndef _MX_RESOURCE_I_TEXTURE_RESOURCE_H_
#define _MX_RESOURCE_I_TEXTURE_RESOURCE_H_

#include "IResource.h"
#include "mxType.h"

namespace mx
{
	namespace resource
	{
		class ITextureResource : public IResource
		{
		public:
			virtual ~ITextureResource(){}

			//取得纹理数据
			ubyte *GetData();
		};
	}
}

#endif