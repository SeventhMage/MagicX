/************************************************************************/
/* ÇòÌå                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_SHPERE_ENTITY_H_
#define _MX_SCENE_C_SHPERE_ENTITY_H_

#include "CEntity.h"
#include "CSphere.h"
#include "render/renderobject/CReflectObject.h"
#include "render/IRenderable.h"

namespace mx
{
	namespace scene
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