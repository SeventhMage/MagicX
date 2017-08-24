#ifndef _RESOURCE_I_MATERIAL_LOADER_H_
#define _RESOURCE_I_MATERIAL_LOADER_H_

#include "IResource.h"

#include <string>

namespace se
{
	namespace resource
	{
		enum EMaterialResAttr
		{
			MRA_UNVALID = -1,
			MRA_COLOR = 0,
			MRA_ILLUMINATION,

			MRA_COUNT,
		};

		class IMaterialResource : public IResource
		{
		public:
			virtual ~IMaterialResource(){}
			virtual int GetAttrCount() = 0;			
			virtual std::string GetValueByIdx(int index) = 0;
			virtual std::string GetValue(EMaterialResAttr attr) = 0;
		};
	}
}

#endif