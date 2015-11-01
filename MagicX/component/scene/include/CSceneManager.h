#ifndef _C_SCENE_MANAGER_H_
#define _C_SCENE_MANAGER_H_

#include "IScene.h"
#include "common/CSingleton.h"
#include "IRenderer.h"
#include "ITerrainSceneNode.h"
#include "IWaterSceneNode.h"

#include <list>

namespace mx
{
	namespace scene
	{
		class CSceneManager
		{
		public:
			CSceneManager(render::IRenderer *renderer);
			virtual ~CSceneManager();

			void Update(uint escapeTime);
			void Render();

			//创建场景
			IScene *CreateScene();

			//创建场景内对象
			ICameraSceneNode *CreateCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip);
			ISkyBoxSceneNode *CreateSkyBox(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom);
			ITerrainSceneNode *CreateTerrain(const char *filename);
			ITerrainSceneNode *CreateRandomTerrain(uint width);
			IWaterSceneNode *CreateWater(const char *filename);
			
			void DeleteCamera(ICameraSceneNode *camera);
			void DeleteSkyBox(ISkyBoxSceneNode *skybox);
			void DeleteTerrain(ITerrainSceneNode *terrain);
			void DeleteWater(IWaterSceneNode *water);

			void AddSceneNode(IScene *scene, ISceneNode *sceneNode);
			void RemoveSceneNode(IScene *scene, ISceneNode *sceneNode);

			void SetupCamera(IScene *scene, ICameraSceneNode *camera);
			void SetupSkyBox(IScene *scene, ISkyBoxSceneNode *skybox);
			void SetupTerrain(IScene *scene, ITerrainSceneNode *terrain);

			




		private:			
			render::IRenderer *m_pRenderer;

			std::list<IScene *> m_listScene;
			std::list<ICameraSceneNode *> m_listCamera;
			std::list<ISkyBoxSceneNode *> m_listSkyBox;
			std::list<ITerrainSceneNode *> m_listTerrain;
		};
	}
}

#endif