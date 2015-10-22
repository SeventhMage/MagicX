#ifndef _MX_SCENE_C_SCENE_H_
#define _MX_SCENE_C_SCENE_H_

#include "../include/IScene.h"
#include "CCamera.h"

namespace mx
{
	namespace scene
	{
		class CScene : public IScene
		{
		public:
			CScene();
			virtual ~CScene();

			virtual void AddSceneNode(ISceneNode *pSceneNode);
			virtual void RemoveSceneNode(ISceneNode * pSceneNode);
			virtual void RemoveAll() = 0;

			virtual bool LoadScene(const char *filename);

			virtual ISkyBox *CreateSkyBox(const char *filename);
			virtual ITerrainSceneNode *CreateTerrain(const char *filename);

			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up);

			virtual void Render();
		private:
			CCamera *m_camera;
		};
	}
}

#endif
