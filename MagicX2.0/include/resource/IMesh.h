#ifndef _MX_RESOURCE_IMESH_H_
#define _MX_RESOURCE_IMESH_H_

#include "IReferenceCount.h"
#include "mxType.h"

namespace mx
{
	namespace resource
	{
		class IMesh : public IReferenceCount
		{
		public:
			virtual ~IMesh(){}
			virtual byte *GetVerticesData() const = 0;
			virtual uint GetVerticesSize() const = 0;
			virtual uint GetVerticesCount() const = 0;
			virtual uint GetVertexStride() const = 0;
			virtual byte *GetIndicesData() const = 0;
			virtual uint GetIndicesSize() const = 0;
			virtual uint GetIndicesCount() const = 0;
		};
	}
}

#endif