/************************************************************************/
/* ÇòÌå                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_SHPERE_H_
#define _MX_SCENE_C_SHPERE_H_

#include "CEntity.h"
#include "render/IVertexArrayObject.h"
#include "render/ITexture.h"
#include "render/IRenderable.h"

namespace mx
{
	namespace scene
	{
		using namespace render;
		class CSphere : public CEntity
		{
		public:
			CSphere(IScene *pScene, float fRadius, int iSlices, int iStacks);
			virtual ~CSphere();
			virtual void UpdateImp(int delta);
			virtual void RenderImp();
		private:
			IVertexArrayObject *m_pVAO;
			ITexture *m_pTexture;
			IRenderable *m_pRenderable;
		};
	}
}

#endif