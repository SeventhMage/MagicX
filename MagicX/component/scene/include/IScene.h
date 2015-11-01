#ifndef _I_SCENE_H_INC_
#define _I_SCENE_H_INC_

#include "ISceneNode.h"
#include "ISkyBoxSceneNode.h"
#include "ICameraSceneNode.h"
#include "ITerrainSceneNode.h"

namespace mx
{
	namespace scene
	{
		class IScene
		{
		public:
			IScene(){}
			virtual ~IScene(){}

			virtual void AddSceneNode(ISceneNode *pSceneNode) = 0;
			virtual void RemoveSceneNode(ISceneNode * pSceneNode) = 0;	
			virtual void RemoveAll() = 0;
			
			virtual bool LoadScene(const char *filename) = 0;			

			virtual void SetupCamera(ICameraSceneNode *camera) = 0;
			virtual void SetupSkyBox(ISkyBoxSceneNode *skybox) = 0;
			virtual void SetupTerrain(ITerrainSceneNode *terrain) = 0;

			virtual void Update(int elapsedTime) = 0;
		};
	}
}

#endif