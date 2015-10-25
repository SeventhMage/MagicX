#ifndef _MX_SCENE_C_SCENE_H_
#define _MX_SCENE_C_SCENE_H_

#include "../include/IScene.h"
#include "CCamera.h"
#include "IRenderer.h"

namespace mx
{
	namespace scene
	{
		class CScene : public IScene
		{
		public:
			CScene(render::IRenderer *renderer);
			virtual ~CScene();

			virtual void AddSceneNode(ISceneNode *pSceneNode);
			virtual void RemoveSceneNode(ISceneNode * pSceneNode);
			virtual void RemoveAll();

			virtual bool LoadScene(const char *filename);

			virtual ISkyBox *CreateSkyBox(const char *filename);
			virtual ISkyBox *CreateSkyBox(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom);
			virtual ITerrainSceneNode *CreateTerrain(const char *filename);

			virtual ICamera *SetupCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float near, float far);

			virtual void Update(int elapsedTime);
			virtual void Render();
		private:
			CCamera *m_pCamera;
			ISkyBox *m_pSkyBox;
			render::IRenderer *m_pRenderer;
		};
	}
}

#endif
