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
			virtual ~IBufferObject();
		};
	}
}

#endif