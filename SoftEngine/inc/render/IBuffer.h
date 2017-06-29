#ifndef _RENDER_I_BUFFER_H_
#define _RENDER_I_BUFFER_H_

#include "base/seType.h"
#include "VertexAttribute.h"

namespace se
{
	namespace render
	{
		enum EBufferType
		{
			BT_CPU,
			BT_GPU,
		};
		class IBuffer
		{
		public:
			virtual ~IBuffer(){}
			virtual uint GetID()const = 0;
			virtual EBufferType GetBufferType()const = 0;
			virtual void BufferData(const SIndexData &) = 0;
			virtual IndexData *GetIndexData() = 0;
			virtual VertexData *GetVertexData() = 0;
		};
	}
}

#endif