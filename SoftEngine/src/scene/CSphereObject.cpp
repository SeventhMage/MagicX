#include "CSphereObject.h"

namespace se
{
	namespace scene
	{
		CSphereObject::CSphereObject(uint id, float fRadius, const render::Color &color)
			:CObject(id), m_fRadius(fRadius), m_Color(color)
		{

		}

		CSphereObject::~CSphereObject()
		{

		}

		bool CSphereObject::Interset(const math::CRay &ray, math::CVector3 *hitPoint /*= nullptr*/, render::SColor *hitColor /*= nullptr*/)
		{

			return false;
		}

	}
}