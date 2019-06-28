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
			RT_IMAGE = 0,			//图片资源
			RT_MESH,				//网络资源
			RT_SOUND,				//声音资源
			RT_TABLE_CONFIG,		//配置表

			RT_COUNT,
		};

		class IResource
		{
		public:
			virtual ~IResource(){}

			//virtual EResourceType GetResourceType() = 0;
		};
	}
}

#endif