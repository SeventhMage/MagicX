/************************************************************************/
/* ³¡¾°                                                                 */
/************************************************************************/

#ifndef _MX_SCENE_C_SCENE_H_
#define _MX_SCENE_C_SCENE_H_

#include "scene/IScene.h"

namespace mx
{
	namespace scene
	{
		class CScene : public IScene
		{
		public:
			CScene();
			virtual ~CScene();

			virtual ISceneNode *GetRootNode() { return m_pRootNode; }
			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction,
				const CVector3 &up, float fov, float aspect, float nearClip, float farClip);
			virtual ICamera *GetCamera();
			virtual void Update(int delta);
			virtual void Draw();

		private:
			ISceneNode *m_pRootNode;
			ICamera *m_pCamera;
		};
	}
}

#endif