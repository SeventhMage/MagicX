#ifndef _SCENE_C_SPHERE_OBJECT_H_
#define _SCENE_C_SPHERE_OBJECT_H_

#include "CObject.h"

namespace se
{
	namespace scene
	{
		class CSphereObject : public CObject
		{
		public:
			CSphereObject(uint id, float fRadius, const render::Color &color);
			~CSphereObject();
			bool Interset(const math::CRay &ray, math::CVector3 *hitPoint = nullptr, render::Color *hitColor = nullptr);
		private:
			float m_fRadius;
			render::Color m_Color;
		};
	}
}

#endif