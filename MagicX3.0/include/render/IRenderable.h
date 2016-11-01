/************************************************************************/
/* 每个renderable存储了对渲染器的一次提交                               */
/************************************************************************/

#ifndef _MX_RENDER_I_RENDERABLE_H_
#define _MX_RENDER_I_RENDERABLE_H_

#include "IBufferObject.h"

namespace mx
{
	namespace render
	{
		class IRenderable
		{
		public:
			virtual ~IRenderable(){}

			//生成缓冲区对象
			virtual IBufferObject *CreateBufferObject(EBufferObjectType type);
			
			virtual 
		};
	}
}

#endif