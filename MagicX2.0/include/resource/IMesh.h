#ifndef _MX_RESOURCE_IMESH_H_
#define _MX_RESOURCE_IMESH_H_

#include "core/CMatrix4.h"
#include "core/CVector3.h"
#include "IResource.h"
#include "mxType.h"

namespace mx
{
	namespace resource
	{
		using core::CMatrix4;
		using core::CVector3;
		class IMesh : public IResource
		{
		public:
			virtual ~IMesh(){}
			virtual void rotateXZBy(double radians, const CVector3 &center = CVector3(0, 1.0f, 0)) = 0;
			virtual void rotateXYBy(double radians, const CVector3 &center = CVector3(0, 0, 1.0f)) = 0;
			virtual void rotateYZBy(double radians, const CVector3 &center = CVector3(1.0f, 0, 0)) = 0;
			virtual void Update(uint deltaTime, const CMatrix4 &mat4VP) = 0;
		};
	}
}

#endif