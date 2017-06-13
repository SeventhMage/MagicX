#ifndef _RESOURCE_I_MATERIAL_LOADER_H_
#define _RESOURCE_I_MATERIAL_LOADER_H_

#include "IResource.h"

#include <string>

namespace se
{
	namespace resource
	{
		class IMaterialResource : public IResource
		{
		public:
			virtual ~IMaterialResource(){}
			virtual int GetAttrCount() = 0;
			virtual std::string GetAttrByIdx(int index) = 0;
			virtual std::string GetValueByIdx(int index) = 0;
			virtual std::string GetValue(const std::string &attr) = 0;
		};
	}
}

#endif