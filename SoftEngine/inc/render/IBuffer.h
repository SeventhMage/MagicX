#ifndef _RENDER_I_BUFFER_H_
#define _RENDER_I_BUFFER_H_

#include "base/seType.h"
#include "base/VertexAttribute.h"

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
			virtual void BufferData(const base::Vertices *) = 0;
			virtual void BufferData(const base::Indices *) = 0;
			virtual base::Vertices *GetVertices() = 0;
			virtual base::Indices *GetIndices() = 0;
		};
	}
}

#endif