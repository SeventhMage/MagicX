/************************************************************************/
/* ÇòÌå                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_SHPERE_ENTITY_H_
#define _MX_SCENE_C_SHPERE_ENTITY_H_

#include "CEntity.h"
#include "CSphere.h"
#include "CReflectObject.h"

namespace mx
{
	namespace scene
	{
		using namespace render;
		class CSphereEntity : public CEntity
		{
		public:
			CSphereEntity(IScene *pScene, float fRadius, int iSlices, int iStacks);
			virtual ~CSphereEntity();
			virtual void UpdateImp(int delta);
			virtual void RenderImp();

			void CreateReflect();
		private:
			CSphere *m_pSphere;
			CReflectObject *m_pReflectObject;
		};
	}
}

#endif