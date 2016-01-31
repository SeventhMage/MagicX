#ifndef _MX_RENDER_I_BUFFER_OBJECT_H_
#define _MX_RENDER_I_BUFFER_OBJECT_H_

#include "mxType.h"

namespace mx
{
	namespace render
	{
		class IBufferObject
		{
		public:
			virtual ~IBufferObject() {};
			virtual void BufferData(void *data, int size) = 0;
			virtual void BufferSubData(void *data, int size, int offset) = 0;
			virtual uint GetHandle() const = 0;
		};
	}
}

#endif

