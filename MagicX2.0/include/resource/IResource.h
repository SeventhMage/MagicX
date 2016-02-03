#ifndef _MX_RESOURCE_IRESOURCE_H_
#define _MX_RESOURCE_IRESOURCE_H_

#include "IReferenceCount.h"

namespace mx
{
	namespace resource
	{
		class IResource : public IReferenceCount
		{
		public:
			virtual ~IResource(){};
			virtual bool Load(const char *filename) = 0;

		};
	}
}

#endif