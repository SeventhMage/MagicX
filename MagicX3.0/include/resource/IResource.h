/************************************************************************/
/* ��Դ�ӿ�                                                             */
/************************************************************************/

#ifndef _MX_RESOURCE_I_RESOURCE_H_
#define _MX_RESOURCE_I_RESOURCE_H_

namespace mx
{
	namespace resource
	{
		//��Դ����
		enum EResourceType
		{
			RT_IMAGE = 0,			//ͼƬ��Դ
			RT_MESH,				//������Դ
			RT_SOUND,				//������Դ
			RT_TABLE_CONFIG,		//���ñ�

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