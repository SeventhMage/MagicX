#ifndef _SCENE_I_OBJECT_H_
#define _SCENE_I_OBJECT_H_

#include "render/SColor.h"
#include "math/CVector3.h"
#include "math/CRay.h"

namespace se
{
	namespace scene
	{
		class IObject
		{
		public:
			virtual ~IObject(){}
			virtual bool Interset(const math::CRay &ray, math::CVector3 *hitPoint = nullptr) = 0;
			virtual uint GetID() const  = 0;
		protected:
		private:
		};
	}
}

#endif