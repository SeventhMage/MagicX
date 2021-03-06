#ifndef _RESOURCE_I_MATERIAL_LOADER_H_
#define _RESOURCE_I_MATERIAL_LOADER_H_

#include "IResource.h"

#include <string>
#include "base/seType.h"

namespace se
{
	namespace resource
	{
		enum EMaterialResAttr
		{
			MRA_UNVALID = -1,
			MRA_COLOR = 0,
			MRA_ILLUMINATION,
			MRA_AMBIENT_COE,
			MRA_DIFFUSE_COE,
			MRA_SPECULAR_COE,
			MRA_SPECULARITY_COE,

			MRA_COUNT,
		};

		class IMaterialResource : public IResource
		{
		public:
			virtual ~IMaterialResource(){}
			virtual int GetAttrCount() = 0;			
			virtual std::string GetValueByIdx(uint index) = 0;
			virtual std::string GetValue(EMaterialResAttr attr) = 0;
		};
	}
}

#endif