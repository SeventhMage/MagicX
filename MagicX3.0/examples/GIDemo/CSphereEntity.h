#ifndef _EXAMPLE_C_SPHERE_ENTITY_H_ 
#define _EXAMPLE_C_SPHERE_ENTITY_H

#include "scene/CEntity.h"
#include "scene/CSphere.h"
#include "render/IRenderable.h"
#include "math/CVector3.h"

namespace mx
{
	namespace ex
	{
		using namespace render;
		using namespace math;
		class CSphereEntity : public scene::CEntity
		{
		public:
			CSphereEntity(float fRadius, int iSlices, int iStacks, const CVector3 &color = CVector3(1.0f, 1.0f, 1.0f));
			virtual ~CSphereEntity();
			virtual void UpdateImp(int delta);

			void Create();
			float GetRadius() { return m_fRadius; }
		private:
			scene::CSphere *m_pSphere;
			float m_fRadius;
			CVector3 m_vColor;
		};
	}

}

#endif
