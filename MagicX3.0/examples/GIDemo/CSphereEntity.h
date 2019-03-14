#ifndef _EXAMPLE_C_SPHERE_ENTITY_H_ 
#define _EXAMPLE_C_SPHERE_ENTITY_H

#include "scene/CEntity.h"
#include "scene/CSphere.h"
#include "render/IRenderable.h"

namespace mx
{
	namespace ex
	{
		using namespace render;
		class CSphereEntity : public scene::CEntity
		{
		public:
			CSphereEntity(float fRadius, int iSlices, int iStacks);
			virtual ~CSphereEntity();
			virtual void UpdateImp(int delta);

			void Create();
			float GetRadius() { return m_fRadius; }
		private:
			scene::CSphere *m_pSphere;
			float m_fRadius;
		};
	}

}

#endif
