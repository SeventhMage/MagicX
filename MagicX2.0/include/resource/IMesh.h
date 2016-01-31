#ifndef _MX_RESOURCE_IMESH_H_
#define _MX_RESOURCE_IMESH_H_

#include "IReferenceCount.h"

namespace mx
{
	namespace resource
	{
		class IMesh : public IReferenceCount
		{
		public:
			virtual ~IMesh(){}

		};
	}
}

#endif