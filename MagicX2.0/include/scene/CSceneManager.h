#ifndef _C_SCENE_MANAGER_H_
#define _C_SCENE_MANAGER_H_

#include "IScene.h"
#include "core/CSingleton.h"
#include "scene/ITerrain.h"
#include "scene/IWater.h"
#include "render/IRenderer.h"

#include <list>

namespace mx
{
	namespace scene
	{
		class CSceneManager
		{
		public:
			CSceneManager(render::IRenderer *pRenderer);
			virtual ~CSceneManager();

			void Update(uint escapeTime);

			//创建场景
			IScene *CreateScene();

			//创建场景内对象
			ICamera *CreateCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip);
			ISkyBox *CreateSkyBox(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom, float radius);
			ITerrain *CreateTerrain(const char *filename);
			ITerrain *CreateRandomTerrain(uint width);
			IWater *CreateWater(const char *filename);
			
			void DeleteCamera(ICamera *camera);
			void DeleteSkyBox(ISkyBox *skybox);
			void DeleteTerrain(ITerrain *terrain);
			void DeleteWater(IWater *water);

			void AddSceneNode(IScene *scene, ISceneNode *sceneNode);
			void RemoveSceneNode(IScene *scene, ISceneNode *sceneNode);

			void SetupCamera(IScene *scene, ICamera *camera);
			void SetupSkyBox(IScene *scene, ISkyBox *skybox);
			void SetupTerrain(IScene *scene, ITerrain *terrain);

		private:			
			render::IRenderer *m_pRenderer;
			std::list<IScene *> m_listScene;
			std::list<ICamera *> m_listCamera;
			std::list<ISkyBox *> m_listSkyBox;
			std::list<ITerrain *> m_listTerrain;
		};
	}
}

#endif