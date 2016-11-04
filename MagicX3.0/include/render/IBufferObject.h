/************************************************************************/
/* 缓冲区对象                                                           */
/************************************************************************/

#ifndef _MX_RENDER_I_BUFFER_OBJECT_H_
#define _MX_RENDER_I_BUFFER_OBJECT_H_

namespace mx
{
	namespace render
	{
		enum EBufferObjectType
		{
			BOT_VERTEX,		//顶点缓冲区对象
			BOT_INDEX,		//索引缓冲区对象
		};

		class IBufferObject
		{
		public:
			virtual ~IBufferObject(){}

			//绑定到当前缓冲区对象
			virtual void Bind() = 0;
			virtual void UnBind() = 0;
			virtual void BufferData(void *data, int size) = 0;
			virtual void BufferSubData(void *data, int size, int offset) = 0;
		};
	}
}

#endif