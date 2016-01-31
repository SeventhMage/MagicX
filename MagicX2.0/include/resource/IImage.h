#ifndef _MX_RESOURCE_IIMAGE_H_
#define _MX_RESOURCE_IIMAGE_H_

#include "IReferenceCount.h"

namespace mx
{
	namespace resource
	{
		class IImage : public IReferenceCount
		{
		public:
			virtual ~IImage(){}
		};
	}
}

#endif