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
			virtual ~IBufferObject(){}

			//�󶨵���ǰ����������
			virtual void Bind() = 0;
			virtual void UnBind() = 0;
			virtual void BufferData(void *data, int size) = 0;
			virtual void BufferSubData(void *data, int size, int offset) = 0;
		};
	}
}

#endif