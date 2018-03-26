#ifndef _SE_RENDER_I_VERTEX_ARRAY_OBJECT_H_
#define _SE_RENDER_I_VERTEX_ARRAY_OBJECT_H_

#include "base/seType.h"

namespace se
{
	namespace render
	{
		class IVertexArrayObject
		{
		public:
			virtual ~IVertexArrayObject(){}
			virtual uint GetID() const = 0;
			virtual void VertexAttrPointer(uint index, uint size, EDataType type, uint stride, uint offset) = 0;
		};
	}
}

#endif