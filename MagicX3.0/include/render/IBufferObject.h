/************************************************************************/
/* ����������                                                           */
/************************************************************************/

#ifndef _MX_RENDER_I_BUFFER_OBJECT_H_
#define _MX_RENDER_I_BUFFER_OBJECT_H_

namespace mx
{
	namespace render
	{
		enum EBufferObjectType
		{
			BOT_VERTEX,		//���㻺��������
			BOT_INDEX,		//��������������
		};

		class IBufferObject
		{
		public:
			virtual ~IBufferObject();
		};
	}
}

#endif