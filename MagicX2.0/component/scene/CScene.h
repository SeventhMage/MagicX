#ifndef _MX_SCENE_C_SCENE_H_
#define _MX_SCENE_C_SCENE_H_

#include "scene/IScene.h"
#include "CCamera.h"
#include "render/IRenderer.h"


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
			virtual void RemoveAll();

			virtual bool LoadScene(const char *filename);

			virtual void SetupCamera(ICamera *camera);
			virtual void SetupSkyBox(ISkyBox *skybox);
			virtual void SetupTerrain(ITerrain *terrain);

			virtual ICamera *GetCamera() { return m_pCamera; };

			virtual void Update(int elapsedTime);
			virtual void Render();
		private:
			ISceneNode *m_pRootNode;
			render::IRenderer *m_pRenderer;
			ICamera *m_pCamera;
			ISkyBox *m_pSkyBox;
			ITerrain *m_pTerrain;
		};
	}
}

#endif
