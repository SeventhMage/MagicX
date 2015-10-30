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

			virtual void SetupCamera(ICameraSceneNode *camera);
			virtual void SetupSkyBox(ISkyBoxSceneNode *skybox);
			virtual void SetupTerrain(ITerrainSceneNode *terrain);

			virtual void Update(int elapsedTime);
		private:
			ISceneNode *m_pRootNode;
			render::IRenderer *m_pRenderer;
			ICameraSceneNode *m_pCamera;			
			ISkyBoxSceneNode *m_pSkyBox;
			ITerrainSceneNode *m_pTerrain;
		};
	}
}

#endif
