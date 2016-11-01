/************************************************************************/
/* 资源接口                                                             */
/************************************************************************/

#ifndef _MX_RESOURCE_I_RESOURCE_H_
#define _MX_RESOURCE_I_RESOURCE_H_

namespace mx
{
	namespace resource
	{
		//资源类型
		enum EResourceType
		{
			RT_TEXTURE,			//纹理资源
			RT_MESH,			//网络资源
			RT_SOUND,			//声音资源
		};

		class IResource
		{
		public:
			virtual ~IResource(){}

			virtual EResourceType GetResourceType() = 0;
		};
	}
}

#endif