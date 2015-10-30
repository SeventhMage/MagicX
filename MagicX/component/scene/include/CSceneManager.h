#ifndef _C_SCENE_MANAGER_H_
#define _C_SCENE_MANAGER_H_

#include "IScene.h"
#include "common/CSingleton.h"
#include "IRenderer.h"
#include "ITerrainSceneNode.h"
#include "IWaterSceneNode.h"

#include <map>

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
			uint CreateScene();

			//创建场景内对象
			uint CreateCamera(const CVector3 &position, const CVector3 &direction, const CVector3 &up, float fov, float aspect, float nearClip, float farClip);
			uint CreateSkyBox(const char *front, const char *back, const char * left, const char *right, const char *top, const char *bottom);
			uint CreateTerrain(const char *filename);
			uint CreateWater(const char *filename);
			
			void AddSceneNode(uint scene, ISceneNode *sceneNode);
			void AddWater(uint scene, uint water);
			void SetupCamera(uint scene, uint camera);
			void SetupSkyBox(uint scene, uint skybox);
			void SetupTerrain(uint scene, uint terrain);

			void RemoveSceneNode(uint scene, ISceneNode *sceneNode);
			void RemoveWater(uint scene, uint water);

			void DeleteCamera(uint camera);
			void DeleteSkyBox(uint skybox);
			void DeleteTerrain(uint terrain);


		private:			
			render::IRenderer *m_pRenderer;

			std::map<uint, IScene *> m_mapScene;

			std::map<uint, ICameraSceneNode *> m_mapCamera;
			std::map<uint, ISkyBoxSceneNode *>m_mapSkyBox;
			std::map<uint, ITerrainSceneNode *>m_mapTerrain;
		};
	}
}

#endif