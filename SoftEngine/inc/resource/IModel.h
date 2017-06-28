#ifndef _RESOURCE_I_MODEL_H_
#define _RESOURCE_I_MODEL_H_

#include "IResource.h"

namespace se
{
	namespace resource
	{
		//ÃæË÷Òý
		struct SFaceIndex
		{
			int position;
			int texcoord;
			int normal;
		};

		struct SPolygon
		{
			std::vector<math::CVector3> positionList;
			std::vector<math::CVector3> normalList;
			std::vector<math::CVector2> texCoordList;
			std::vector<SFaceIndex> faceList;
		};

		class IModel : public IResource
		{
		public:
			virtual ~IModel(){}
			virtual std::string GetMaterial() = 0;
			virtual std::string GetTexture() = 0;
			virtual SPolygon &GetPolygon() = 0;
		};
	}
}

#endif