/************************************************************************/
/* ����                                                                 */
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
		class CSphereEntity : public CEntity
		{
		public:
			CSphereEntity(IRenderObject *pRenderObject, float fRadius, int iSlices, int iStacks);
			virtual ~CSphereEntity();
			virtual void UpdateImp(int delta);			
			
			void Create();
			float GetRadius(){ return m_fRadius; }
		private:
			CSphere *m_pSphere;
			IRenderObject *m_pReflectObject;
			IRenderable *m_pRenderable;
			float m_fRadius;
		};
	}
}

#endif