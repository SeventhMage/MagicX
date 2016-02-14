#ifndef _I_SCENE_H_INC_
#define _I_SCENE_H_INC_

#include "ISceneNode.h"
#include "ISkyBox.h"
#include "ICamera.h"
#include "ITerrain.h"

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

			virtual void SetupCamera(ICamera *camera) = 0;
			virtual void SetupSkyBox(ISkyBox *skybox) = 0;
			virtual void SetupTerrain(ITerrain *terrain) = 0;

			virtual ICamera *GetCamera() = 0;

			virtual void Update(int elapsedTime) = 0;
			virtual void Render() = 0;
		};
	}
}

#endif