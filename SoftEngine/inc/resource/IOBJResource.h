#ifndef _RESOURCE_I_OBJ_RESOURCE_H_
#define _RESOURCE_I_OBJ_RESOURCE_H_

#include "IResource.h"
#include "base/seType.h"

#include "math/CVector3.h"
#include "math/CVector2.h"

namespace se
{
	namespace resource
	{
		struct SFaceIndex
		{
			int indicesCount;
			int position[4];
			int texCoord[4];
			int normal[4];
		};
		using namespace math;

		class IOBJResource : public IResource
		{
		public:
			virtual ~IOBJResource(){}
			virtual const std::vector<CVector3> &GetPositionList() = 0;
			virtual const std::vector<CVector3> &GetNormalList() = 0;
			virtual const std::vector<CVector2> &GetTexCoordList() = 0;
			virtual const std::vector<SFaceIndex> &GetFaceIndexList() = 0;
		};
	}
}

#endif