#ifndef _C_SCENE_MANAGER_H_
#define _C_SCENE_MANAGER_H_

#include "IScene.h"
#include "common/CSingleton.h"
#include "IRenderer.h"
#include "ITerrainSceneNode.h"
#include "IWaterSceneNode.h"

namespace mx
{
	namespace scene
	{
		class CSceneManager : public CSingleton<CSceneManager>
		{
		public:
			friend class CSingleton<CSceneManager>;

			void Update(uint escapeTime);
			void Render();

			IScene *GetCurrentScene() const;
			const std::list<IScene *> &GetSceneList() const;

			IScene *CreateScene(render::IRenderer *renderer);

			virtual ITerrainSceneNode *CreateTerrain(const char *filename);
			virtual IWaterSceneNode *CreateWater(const char *filename);


		private:
			CSceneManager();
			virtual ~CSceneManager();

			std::list<IScene *> m_listScene;
			IScene *m_pCurrentScene;
		};
	}
}

#endif