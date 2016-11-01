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
			RT_TEXTURE,			//������Դ
			RT_MESH,			//������Դ
			RT_SOUND,			//������Դ
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